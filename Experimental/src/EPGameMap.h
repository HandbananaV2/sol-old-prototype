/*
 * EPGameMap.h
 *
 *  Created on: Jun. 16, 2020
 *      Author: Michel
 */

#ifndef EPGAMEMAP_H_
#define EPGAMEMAP_H_

#include <SFML/Graphics.hpp>
#include <vector>

class EPDrawable;
class EPInteractable;
class EPPlayerObject;

class EPGameMap
{
public:
    static constexpr unsigned int BlockWidth = 1024;
    static constexpr unsigned int BlockHeight = 768;
    static constexpr unsigned int SegmentCount = 8;
    //
    struct SegmentData
    {
        sf::Sprite _block;
        sf::Texture _texture;
        int origin_x, origin_y;
    };
    //
    struct SolidData
    {
        sf::FloatRect target;
        int mode;
    };
    /*
     *
     */
    float m_offset_x, m_offset_y;
    /*
     *
     */
    SegmentData mSegments[SegmentCount][SegmentCount];
    std::vector<SolidData> mSolids[SegmentCount][SegmentCount];
    /*
     *
     */
    std::vector<EPDrawable*> mUseables;
    typedef std::vector<EPDrawable*>::iterator UsableIterator;
    /*
     *
     */
    std::vector<EPDrawable*> mDynamics;
    typedef std::vector<EPDrawable*>::iterator DyanicIterator;
    /*
     *
     */
    EPGameMap();
    /*
     *
     */
    ~EPGameMap();
    /*
     *
     */
    void update(float);
    /*
     *
     */
    void draw(sf::RenderWindow*);
    /*
     *
     */
    void bind_segment();
    /*
     *
     */
    void assignInteractable(EPDrawable*);
    /*
     *
     */
    bool isOverlappingSolid(const sf::FloatRect &A);
    /*
     *
     */
    void spawnPlayer(EPPlayerObject* = nullptr);
    /*
     *
     */
    void sleep();
    /*
     *
     */
    void wakeup();
    /*
     *
     */
    EPDrawable* lookupUseObject(const sf::FloatRect&, int aimDir, float range);
    /*
     *
     */
    EPGameMap::SegmentData* allocateSegment(int, int);
    /*
     *
     */
    std::vector<EPGameMap::SolidData>* allocateSolid(int, int);
    /*
     *
     */
    int m_width, m_height;
    float m_start_x, m_start_y;
    /*
     *
     */
    sf::Sprite mSkybox;
    sf::Texture mSkyboxTexture;

    std::string m_name;

};

#endif /* EPGAMEMAP_H_ */
