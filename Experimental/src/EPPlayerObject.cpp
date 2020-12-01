/*
 * EPPlayerObject.cpp
 *
 *  Created on: Jun. 19, 2020
 *      Author: Michel
 */

#include "EPPlayerObject.h"
#include "EPGameMap.h"
#include "EPBase.h"

#include <usefullib/utility.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#include "UGUIStaticImage.h"



/*
 *
 */
EPPlayerObject::EPPlayerObject() :
    EPAIDoll(nullptr, "Player")
{
    m_immobile = 0;
    m_useRange = 0.75f;

    // 1.0 is 10 health points.
    m_health = 1.0;
    m_max_health = 1.0;

    mHotBar = nullptr;
    mHotbarSelect = nullptr;
    mHeartOverlay = nullptr;


    mHotbarInfo.index = 0; // Indexes: Multiples of 64
}
/*
 *
 */
EPPlayerObject::~EPPlayerObject()
{
    delete mHeartOverlay;
    delete mHotbarSelect;
    delete mHotBar;
}
/*
 *
 */
void EPPlayerObject::initialise()
{

    // Hotbar
    this->mHotBar = new UGUI_StaticImage("#hot-bar");
    this->mHotBar->setPosition((1280 / 2) - (512 / 2), 955);

    this->mHotbarSelect = new UGUI_StaticImage("#hot-bar-select");
    this->mHotbarSelect->setPosition(((1280 / 2) - (512 / 2)) + this->mHotbarInfo.index*64, 955);

    // health overlay
    this->mHeartOverlay = new UGUI_StaticImage("#heart-overlay");
    this->mHeartOverlay->setPosition(16,16);

    // Sprites
    sf::IntRect heartIcons[] =
    {
        sf::IntRect(0,0,16,26),
        sf::IntRect(0,28,32,25),
        sf::IntRect(0,56,32+16,25),

        sf::IntRect(0,81,64,25),
        sf::IntRect(0,107,64+16,25),
        sf::IntRect(0,135,96,25),

        sf::IntRect(0,160,96+16,25),
        sf::IntRect(0,188,128,25),
        sf::IntRect(0,215,128+16,25),

        sf::IntRect(0,241,161,26),
    };

    // Load the sprites
    UsefulLibrary::Utility::Gfx::Splice(ExperimentalProject::G_ApplicationRoot + "resources/sprites/UI/ui/hearts.png", heartIcons, 10, this->mHearts);
    // Assign our surfaces to the image.
    this->mHeartOverlay->bindSurface(0, this->mHearts[0]);
    this->mHeartOverlay->bindSurface(1, this->mHearts[1]);
    this->mHeartOverlay->bindSurface(2, this->mHearts[2]);

    this->mHeartOverlay->bindSurface(3, this->mHearts[3]);
    this->mHeartOverlay->bindSurface(4, this->mHearts[4]);
    this->mHeartOverlay->bindSurface(5, this->mHearts[5]);

    this->mHeartOverlay->bindSurface(6, this->mHearts[6]);
    this->mHeartOverlay->bindSurface(7, this->mHearts[7]);
    this->mHeartOverlay->bindSurface(8, this->mHearts[8]);

    this->mHeartOverlay->bindSurface(9, this->mHearts[9]);

    // Bind the first heart to the image
    this->mHeartOverlay->bindSurface(9);

    // Load othersprites
    mBars[0].loadFromFile(ExperimentalProject::G_ApplicationRoot + "/resources/sprites/UI/ui/hot-bar.png");
    mBars[1].loadFromFile(ExperimentalProject::G_ApplicationRoot + "/resources/sprites/UI/ui/hot-bar-select.png");

    this->mHotBar->bindSurface(0, mBars[0]);
    this->mHotBar->bindSurface(0);

    this->mHotbarSelect->bindSurface(0, mBars[1]);
    this->mHotbarSelect->bindSurface(0);

    // The files(0-3) associated with the rectangles list.
    std::string file_paths[] =
    {
        ExperimentalProject::G_ApplicationRoot + "resources/sprites/Human (Back)/full_preview.png",
        ExperimentalProject::G_ApplicationRoot + "resources/sprites/Human (Side)/full_preview.png",
        ExperimentalProject::G_ApplicationRoot + "resources/sprites/Human (Side)/full_preview_right.png",
        ExperimentalProject::G_ApplicationRoot + "resources/sprites/Human (Front)/full_preview.png"
    };
    // The list of rectangles(in pixels) to copy from each sheet.
    std::map<int, std::vector<sf::IntRect>> mRectangles
    {
        {
            ANIMUP,
            {
                sf::IntRect( 4, 0, 32, 32 ),
                sf::IntRect( 5, 0, 32, 32 ),
                sf::IntRect( 6, 0, 32, 32 ),
                sf::IntRect( 7, 0, 32, 32 ),
            }
        },
        {
            ANIMLEFT,
            {
                sf::IntRect( 4, 0, 32, 32 ),
                sf::IntRect( 5, 0, 32, 32 ),
                sf::IntRect( 6, 0, 32, 32 ),
                sf::IntRect( 7, 0, 32, 32 ),
            }
        },
        {
            ANIMRIGHT,
            {
                sf::IntRect( 12, 0, 32, 32 ),
                sf::IntRect( 13, 0, 32, 32 ),
                sf::IntRect( 14, 0, 32, 32 ),
                sf::IntRect( 15, 0, 32, 32 ),
            }
        },
        {
            ANIMDOWN,
            {
                sf::IntRect( 4, 0, 32, 32 ),
                sf::IntRect( 5, 0, 32, 32 ),
                sf::IntRect( 6, 0, 32, 32 ),
                sf::IntRect( 7, 0, 32, 32 ),
            }
        }
    };

    std::map<int, std::vector<sf::IntRect>>::iterator blockIterator = mRectangles.begin();
    //
    while (blockIterator != mRectangles.end())
    {
        sf::Image srcImg, tmpImg;
        // The array index containing the animations for the direction(0-3)
        const int index = blockIterator->first;
        // The array of rectangles to load from the sprite sheet.
        const std::vector<sf::IntRect> *rectangles = &blockIterator->second;
        // Throw an error if we can't open the file.
        if (!srcImg.loadFromFile(file_paths[index]))
            throw std::runtime_error("Unable to load image file " + file_paths[index]);
        // Start cutting blocks and loading them.
        for (unsigned int x = 0; x < rectangles->size(); x++)
        {
            // Copy the block into the tmpImage file to be moved to the texture.
            tmpImg.create(32, 32, sf::Color::Transparent);
            // Copy blocks of pixels.
            tmpImg.copy(srcImg, 0, 0,
                        sf::IntRect(rectangles->at(x).left * 32, rectangles->at(x).top * 32, rectangles->at(x).width,
                                    rectangles->at(x).height), true);
            // Create and assign the pixels.
            mTexutres[index][x] = sf::Texture();
            mTexutres[index][x].create(32, 32);
            mTexutres[index][x].loadFromImage(tmpImg);
        }

        ++blockIterator;
    }


    // Bind the first 'front' texture as default.
    mSprite.setTexture(this->mTexutres[3][0]);
    //
    this->setSize(24, 32);

    this->m_health = 1.0;
    this->_update_hearts();
}
/*
 *
 */
const std::string EPPlayerObject::getType() const
{
    return EPDrawable::getType() + ".EPPlayerObject";
}

/*
 *
 */
void EPPlayerObject::perform_action(const unsigned long &mode, const unsigned int &moveDirection)
{
    // Use key
    if (mode == 0)
    {
        // Look for a useable object within range.
        EPDrawable *object = ExperimentalProject::ActiveMap()->lookupUseObject(this->getBoundaries(), moveDirection, m_useRange);
        //
        if (object)
        {
            //
            EPCommandObject cmd = { ACTION_USE, ACTION_USE, 1, this };
            //
            object->sendCommand(ACTION_USE, &cmd);
        }
    }
}
/*
 *
 */
void EPPlayerObject::draw()
{
    EPDrawable::draw();
}
/*
 *
 */
void EPPlayerObject::update(float float1)
{
    if(this->mHotbarSelect)
        this->mHotbarSelect->setPosition(((1280 / 2) - (512 / 2)) + this->mHotbarInfo.index*64, 955);

    static int moveDir = 0;

    // If the player is immobilized do not permit any key actions..
    if (!m_immobile)
    {
        // Movement keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->mSprite.setTexture(mTexutres[ANIMUP][0]);

            if (!this->internal_check_movement(0))
                this->move(0, -1.50);

            moveDir = 0;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->mSprite.setTexture(mTexutres[ANIMRIGHT][0]);

            if (!this->internal_check_movement(1))
                this->move(1.50, 0);

            moveDir = 1;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->mSprite.setTexture(mTexutres[ANIMDOWN][0]);

            if (!this->internal_check_movement(2))
                this->move(0, 1.50);

            moveDir = 2;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->mSprite.setTexture(mTexutres[ANIMLEFT][0]);

            if (!this->internal_check_movement(3))
                this->move(-1.50, 0);

            moveDir = 3;
        }
        /*
         * Controls the scrolling of the world map.
         */
        {
            /*
             *
             */
            float half_x = ExperimentalProject::DisplayWidth / 2;
            float half_y = ExperimentalProject::DisplayHeight  / 2;
            //
            float right_clip = ExperimentalProject::ActiveMap()->m_width;
            float bottom_clip = ExperimentalProject::ActiveMap()->m_height;
            float new_centre_x = half_x, new_centre_y = half_y;
            //
            //
            float player_right = this->getBoundaries().left + this->getBoundaries().width;
            float player_bottom = this->getBoundaries().top + this->getBoundaries().height;
            //
            if (player_right >= half_x && (player_right + half_x < right_clip))
            {
                new_centre_x = player_right;
            }
            //
            else if (player_right + half_x >= right_clip)
            {
                new_centre_x = right_clip - half_x;
            }
            //
            if (player_bottom >= half_y && (player_bottom + half_y < bottom_clip))
            {
                new_centre_y = player_bottom;
            }
            //
            else if (player_bottom + half_y >= bottom_clip)
            {
                new_centre_y = bottom_clip - half_y;
            }

            //
            ExperimentalProject::G_MainView.setCenter(new_centre_x, new_centre_y);
        }
        //
        // Use key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !keyStates['E'])
        {
            this->perform_action(0, moveDir);
            keyStates['E'] = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            keyStates['E'] = false;
        }

        // Hot Bar Keys
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !keyStates['1'])
            {

                keyStates['1'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                keyStates['1'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !keyStates['2'])
            {

                keyStates['2'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                keyStates['2'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !keyStates['3'])
            {

                keyStates['3'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                keyStates['3'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !keyStates['4'])
            {

                keyStates['4'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                keyStates['4'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !keyStates['5'])
            {

                keyStates['5'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            {
                keyStates['5'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && !keyStates['6'])
            {

                keyStates['6'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            {
                keyStates['6'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && !keyStates['7'])
            {

                keyStates['7'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            {
                keyStates['7'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && !keyStates['8'])
            {

                keyStates['8'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            {
                keyStates['8'] = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && !keyStates['9'])
            {

                keyStates['9'] = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            {
                keyStates['9'] = false;
            }
        }
    }
}
/*
 *
 */
bool EPPlayerObject::internal_check_movement(int dir)
{
// Modifed below then checked at the end.
    sf::FloatRect bounds = this->mBounadries;
    std::vector<sf::Vector2i> targets;
    /*
     * We're moving up
     */
    if (dir == 0)
    {
        bounds.top -= 2;
    }
    /*
     * We're moving right
     */
    if (dir == 1)
    {
        bounds.width += 3;
    }
    /*
     * We're moving down
     */
    if (dir == 2)
    {
        bounds.height += 3;
    }
    /*
     * We're moving left
     */
    if (dir == 3)
    {
        bounds.left -= 3;
        bounds.width += 3;
    }
    /*
     * Check for collisions
     *
     * If we're in between segments, search both segments. We may need to implement better logic to differentiate them
     * later.
     *
     * @formatter:off
     */
    if ((bounds.left / ExperimentalProject::DisplayWidth) != ((bounds.left + bounds.width) / ExperimentalProject::DisplayWidth) || (bounds.top / ExperimentalProject::DisplayHeight) != ((bounds.top + bounds.height) / ExperimentalProject::DisplayHeight))
    {
        // Check for overlapping segments.
        targets =
        {
            sf::Vector2i(std::round(bounds.left / ExperimentalProject::DisplayWidth), std::round(bounds.top / ExperimentalProject::DisplayHeight)),
            sf::Vector2i(std::round(bounds.left + bounds.width) / ExperimentalProject::DisplayWidth, std::round(bounds.top + bounds.height) / ExperimentalProject::DisplayHeight)
        };
    }
    else
    {
        // Single segment if no overlap.
        targets =
        {
            sf::Vector2i(std::round(bounds.left / ExperimentalProject::DisplayWidth), std::round(bounds.top / ExperimentalProject::DisplayHeight))
        };
    }
    /*
     * @formatter:on
     */
    unsigned int targetIndex = 0;
    /*
     *
     */
    while (targetIndex != targets.size())
    {
        //
        const sf::Vector2i &target = targets[targetIndex];
        // Get the list of solids.
        std::vector<EPGameMap::SolidData> *elements = &ExperimentalProject::ActiveMap()->mSolids[target.x][target.y];
        //
        for (unsigned int collider = 0; collider < elements->size(); collider++)
        {
            //
            const EPGameMap::SolidData *solid = &elements->at(collider);
            //
            if (solid->target.intersects(bounds))
                return true;
        }

        ++targetIndex;
    }

// Returned if no collision
    return false;
}

/*
*
*/
void EPPlayerObject::draw_ui(sf::RenderWindow*)
{
    if(mHeartOverlay)
        this->mHeartOverlay->display();

    if(mHotBar)
        this->mHotBar->display();

    if(mHotbarSelect)
        this->mHotbarSelect->display();
}
/*
*
*/
void EPPlayerObject::setHealth(double d){
    EPAIDoll::setHealth(d);
    this->_update_hearts();
}
/*
*
*/
void EPPlayerObject::damage(double d){
    EPAIDoll::damage(d);

    this->_update_hearts();
}
/*
*
*/
void EPPlayerObject::heal(double d){
    EPAIDoll::heal(d);
    this->_update_hearts();
}
/*
*
*/
void EPPlayerObject::destroy(){
    EPAIDoll::destroy();
    this->_update_hearts();

}
/*
*
*/
void EPPlayerObject::_update_hearts(){
    //
    // Because '10' is not a valid array value since index 9 is the max, we need to subtract one.
    //
    double heartcnt = std::round(this->m_health * 10.0);
    //
    this->mHeartOverlay->bindSurface((uint32_t)std::max(0.0f, (float)--heartcnt));
}
