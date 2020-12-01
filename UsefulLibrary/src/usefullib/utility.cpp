#include "utility.h"
#include "encoding.h"
#include <stdlib.h>
#include <exception>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace UsefulLibrary;
/*
*
*/
void Utility::ParseEntryArguments(char* args[], int cnt, std::map<std::string, std::string>& store, char delimiter, bool omitRoot, bool omitMiss){
    //
    // Check if we're told to ignore the root path
    //
    if( ! omitRoot ) {
        const std::string& rootPath = std::string(args[0]);
        //
        if( rootPath == "./" || rootPath.empty()) {
                store[".__root"] = "./";
        }
        else if( rootPath.find_first_of('\\') != std::string::npos ) {
            store[".__root"] = rootPath.substr(0, rootPath.find_last_of('\\') + 1);
        }
        else {
            store[".__root"] = rootPath.substr(0, rootPath.find_last_of('/') + 1);
        }
    }
    // No other arguments?
    if( cnt < 1 ) return;
    // Loop through the arguments.
    for( int index = 1; index < cnt; index++ ) {
        //
        const std::string& tmp = std::string(args[index]);
        //
        if(tmp.find_first_of(delimiter) != std::string::npos) {
             //
            std::vector<std::string> elems;
            // This function is used to split a string by a delimiter.
            UsefulLibrary::Encoding::explode(args[index], delimiter, elems);
            //
            store[elems[0]] = elems[1];
        }
        else if(omitMiss) {
            store[ ".__omit" + std::to_string(index)] = tmp;
        }
    }
}
/*
*
*/
void Utility::Gfx::Splice(const std::string& f, const sf::IntRect* arr, uint64_t len, sf::Texture* cnt){
    //
    uint32_t index = 0;
    sf::Image source, tmp_i;
    //
    if( !source.loadFromFile(f) )
        throw std::runtime_error("Utility::Gfx::Splice(): Unable to locate part of path " + f);
    //
    while ( index < len ) {
        tmp_i = sf::Image();
        tmp_i.create(arr[index].width, arr[index].height, sf::Color::Transparent);
        tmp_i.copy(source, 0, 0, arr[index], true);

        if( ! (cnt[index]).loadFromImage(tmp_i) )
            throw std::runtime_error("Utility::Gfx::Splice(): An error occurred while were cutting blocks from the image. Are the blocks the correct size?");


        index++;
    }

}
