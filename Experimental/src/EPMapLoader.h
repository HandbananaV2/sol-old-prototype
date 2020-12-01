/*
 * EPMapLoader.h
 *
 *  Created on: Jun. 16, 2020
 *      Author: Michel
 */

#ifndef EPMAPLOADER_H_
#define EPMAPLOADER_H_

#include <string>

class EPGameMap;

class EPMapLoader
{
public:
    EPMapLoader(const std::string&);
    ~EPMapLoader();

    void load();
    void load_base();
    void load_solids();
    void load_dynamics();
    void load_useables();
    void finialize();

private:
    EPGameMap *m_mapPtr;
    std::string m_path;


};

#endif /* EPMAPLOADER_H_ */
