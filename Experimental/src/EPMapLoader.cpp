/*
 * EPMapLoader.cpp
 *
 *  Created on: Jun. 16, 2020
 *      Author: Michel
 */
#include "interactable/EPInteractableSwitchType.h"
#include "interactable/EPInteractableMapSwitcher.h"
#include "EPInteractable.h"
#include "EPMapLoader.h"
#include "EPGameMap.h"
#include "EPBase.h"
#include "EPDynamicObject.h"

#include <usefullib/encoding.h>
#include <usefullib/json/json.h>

#include <math.h>
#include <stdlib.h>
#include <list>
#include <iostream>

/*
 *
 */
EPMapLoader::EPMapLoader(const std::string &allocator) :
    m_path(UsefulLibrary::Encoding::append_if_not(allocator, '/', "/"))
{

    this->m_mapPtr = new EPGameMap();
}
/*
 *
 */
EPMapLoader::~EPMapLoader()
{

}
/*
 *
 */
void EPMapLoader::load()
{
    std::cout << "Loading map " << this->m_path << std::endl;
    /*
     * We need to read all the files in the directory structure so we can
     * then process them.
     */
    struct dirent *drnt;
    DIR *directory_stream;
    std::list<std::string> files;
    std::list<std::string>::iterator file_iterator;
    // Open the directory stream. Throw an error if there's a problem.
    if ((directory_stream = opendir(this->m_path.c_str())) == NULL)
        throw std::logic_error("Can't open part of path " + this->m_path);
    // Read all files into the `files` list.
    while ((drnt = readdir(directory_stream)) != NULL)
    {
        // Ignore .. and .
        if (!strcmp(drnt->d_name, ".") || !strcmp(drnt->d_name, ".."))
            continue;
        // Ignore directories we only want files
        if (drnt->d_type == DT_DIR)
            continue;

        files.push_back(drnt->d_name);
    }
    // Close the directory stream.
    closedir(directory_stream);
    /*
     *
     */
    file_iterator = files.begin();
    /*
     *
     */
    while (file_iterator != files.end())
    {
        // The file in the directory.
        const std::string &file = (*file_iterator);
        // It MUST be the right type of file.
        if (file.find_first_of(".png") == std::string::npos)
        {
            file_iterator++;
            continue;
        }
        // Get the file name prefix.
        const std::string fileName = file.substr(0, file.find_last_of('.'));
        // Stores the first two numbers separated by a '.'.
        std::vector<std::string> nameSplit;
        // Split the file name
        UsefulLibrary::Encoding::explode(fileName, '.', nameSplit);
        // Figure out which position this block belongs to.
        int target_x = std::stoi(nameSplit[0]);
        int target_y = std::stoi(nameSplit[1]);
        // Allocate a new segment
        EPGameMap::SegmentData *data = m_mapPtr->allocateSegment(target_x, target_y);
        // Assign segment information
        data->_texture = sf::Texture();
        data->_texture.loadFromFile(m_path + file);
        data->_block.setTexture(data->_texture);
        //
        std::cout << "Loading block " << target_x << "," << target_y << std::endl;
        //
        // These are required for smooth scroll locking.
        //
        if ((target_x + 1) * ExperimentalProject::DisplayWidth >= this->m_mapPtr->m_width)
            this->m_mapPtr->m_width = (target_x + 1) * ExperimentalProject::DisplayWidth;
        if ((target_y + 1) * ExperimentalProject::DisplayHeight>= this->m_mapPtr->m_height)
            this->m_mapPtr->m_height = (target_y + 1) * ExperimentalProject::DisplayHeight;

        ++file_iterator;
    }

    this->m_mapPtr->m_start_x = 0;
    this->m_mapPtr->m_start_y = 0;
    this->m_mapPtr->m_offset_x = 0;
    this->m_mapPtr->m_offset_y = 0;


    std::cout << "Map size is " << this->m_mapPtr->m_width << "," << this->m_mapPtr->m_height << std::endl;
}
/*
 *
 */
void EPMapLoader::load_base()
{
    std::string err = "";
    Json::Value root;
    if (!Json::LoadJson(this->m_path + "cfg/base.json", &root, &err))
        throw std::logic_error("EPMapLoader::load_base(): Unable to load base resource file for the active map.\n" + err);
    //
    std::cout << "Loading map configuration..." << std::endl;

    this->m_mapPtr->m_name = root["name"].asString();
    this->m_mapPtr->m_start_x = root["start_point"]["x"].asInt() * 32;
    this->m_mapPtr->m_start_y = root["start_point"]["y"].asInt() * 32;

    if (this->m_mapPtr->m_name.empty())
        throw std::runtime_error("EPMapLoader::load_base(): Map must have a unique name. Name was not given!");
    // Tell us what map we're working on.
    std::cout << "Loading map " << this->m_mapPtr->m_name << std::endl;
    // Add the map to the list.
    ExperimentalProject::PushMap(this->m_mapPtr);
    // This is reset after the initial loop is done.
    ExperimentalProject::G_ActiveMapID = this->m_mapPtr->m_name;
    // Load the skybox
    const Json::Value &skyboxType = root["skybox"]["type"];
    //
    if (!skyboxType.isNull())
    {
        //
        this->m_mapPtr->mSkyboxTexture.loadFromFile("resources/opt/skyboxes/" + skyboxType.asString() + ".png");
        //
        this->m_mapPtr->mSkybox.setTexture(this->m_mapPtr->mSkyboxTexture);
        this->m_mapPtr->mSkybox.setPosition(0, 0);
        //
        std::cout << "Skybox has been set to " << skyboxType.asString() << std::endl;
    }

}
/*
 * Solid objects that are just colliders and serve no other
 * purpose.
 */
void EPMapLoader::load_solids()
{
    std::string err = "";
    Json::Value root;
    if (!Json::LoadJson(this->m_path + "cfg/solids.json", &root, &err))
        throw std::logic_error("EPMapLoader::load_solids(): Unable to load solids resource for the active map.\n" + err);
    // Root element
    Json::Value contents = root["segments"];
    //
    std::cout << "Loading " << contents.size() << " solid items." << std::endl;
    //
    for (unsigned int x = 0; x < contents.size(); x++)
    {
        // Segment block
        const Json::Value segment_block = contents[x];
        // The list of solids for the segment
        const Json::Value segment_solids = contents[x]["solids"];
        // The segment's index [x][y]
        int solid_x = segment_block["segment_x"].asInt();
        int solid_y = segment_block["segment_y"].asInt();
        // Allocate the solids container for the segment.
        std::vector<EPGameMap::SolidData> *solids = this->m_mapPtr->allocateSolid(solid_x, solid_y);
        // Loop through the solids and bind to the segment.
        for (unsigned int s = 0; s < segment_solids.size(); s++)
        {
            // The solid item itself.
            const Json::Value solidItem = segment_solids[s];
            // The size of the object
            float x = solidItem["x"].asFloat();
            float y = solidItem["y"].asFloat();
            float w = solidItem["w"].asFloat();
            float h = solidItem["h"].asFloat();
            // Assign the object to the segment.
            solids->push_back(EPGameMap::SolidData { sf::FloatRect(x, y, w, h), 0 });
        }
    }
}
/*
 *
 */
void EPMapLoader::load_dynamics()
{
    //
    std::string err = "";
    //
    Json::Value root;
    //
    if (!Json::LoadJson(this->m_path + "cfg/dynamics.json", &root, &err))
        throw std::logic_error("EPMapLoader::load_dynamics(): Unable to load solids resource for the active map.\n" + err);
    //
    //
    Json::Value contents = root["segments"];
    //
    std::cout << "Loading " << contents.size() << " dynamic items." << std::endl;
    //
    for (unsigned int x = 0; x < contents.size(); x++)
    {
        // Segment block
        const Json::Value segment_block = contents[x];
        // Position
        const int _x = segment_block["x"].asInt();
        const int _y = segment_block["y"].asInt();
        //
        const std::string class_name = segment_block["class_name"].asString();
        // The properties array for this object.
        const Json::Value propertiesList = segment_block["properties"];
        //
        for (unsigned int pl = 0; pl < propertiesList.size(); pl++)
        {
            //
            const Json::Value propertyItem = propertiesList[pl];
            // Property name
            const std::string propertyName = propertyItem["name"].asString();
            // Property Value
            const std::string propertyValu = propertyItem["value"].asString();
        }
    }

}
/*
 *
 */
void EPMapLoader::load_useables()
{
    std::string err = "";
    Json::Value root;
    if (!Json::LoadJson(this->m_path + "cfg/interactables.json", &root, &err))
        throw std::logic_error("EPMapLoader::load_useables(): Unable to load solids resource for the active map.\n" + err);

    Json::Value contents = root["segments"];
    //
    std::cout << "Loading " << contents.size() << " interactable items." << std::endl;
    //
    for (unsigned int x = 0; x < contents.size(); x++)
    {
        // Segment block
        const Json::Value segment_block = contents[x];
        // Position
        const int _x = segment_block["x"].asInt();
        const int _y = segment_block["y"].asInt();
        const int _w = segment_block["w"].asInt();
        const int _h = segment_block["h"].asInt();
        // Others
        const std::string _class = segment_block["class"].asString();
        const std::string _sub_class = segment_block["subclass"].asString();
        //
        const bool solid = segment_block["solid"].asBool();
        //
        Json::Value perameters = segment_block["parameters"];
        //
        EPInteractable *o_ptr = nullptr;
        //
        if (solid)
        {
            int fixed_x = (_x != 0) ? std::round(_x / ExperimentalProject::DisplayWidth) : 0;
            int fixed_y = (_y != 0) ? std::round(_y / ExperimentalProject::DisplayHeight) : 0;

            this->m_mapPtr->mSolids[fixed_x][fixed_y].push_back(EPGameMap::SolidData { sf::FloatRect(_x, _y, _w, _h), 0 });
        }
        // Class creation
        if (_class == "object_switch")
        {
            //
            o_ptr = new EPInteractable_SwitchType("#switch-type");
            o_ptr->setPosition(_x, _y);
            o_ptr->initialize(&segment_block);
            o_ptr->setSize_L(_w, _h, true); // Logically adjust the size
        }
        // End of the map?
        if (_class == "object_map_switcher")
        {
            o_ptr = new EPInteractable_MapSwitcher("#map-type");
            o_ptr->setPosition(_x, _y);
            o_ptr->initialize(&segment_block);
            o_ptr->setSize_L(_w, _h, true); // Logically adjust the size
        }
    }
}
/*
 *
 */
void EPMapLoader::finialize()
{
    // Hook all the events for objects added to the 'init' list.
    ExperimentalProject::World::ProcessEventLookups(this->m_mapPtr);
}
