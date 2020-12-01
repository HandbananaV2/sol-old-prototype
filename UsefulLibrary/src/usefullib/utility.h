#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace UsefulLibrary {
    /**
    * @namespace Utility
    *
    * Contains utility functions.
    */
    namespace Utility
    {
           /**
           * Parses the arguments passed to main. The prefix and suffix will be separated by the delimiter.
           *
           * Keep in mind that the first argument <b>will be the root directory</b>.
           *
           * Strings that do not contain the delimiter
           *
           * @name ParseEntryArguments
           * @param char* args[]
           * @param int count
           * @param std::map<std::string, std::String>&
           * @param char delimiter - Default is '='
           * @param bool (optional) Tells the system to not store the root path in the first entry.
           * @param bool (optional) Tells the system to not store any strings that cannot be split.
           *
           * @return void
           */
           void ParseEntryArguments(char* args[], int cnt, std::map<std::string, std::string>&, char delimiter = '=', bool omitRoot = false, bool omitMiss = false);
           /**
           * @namespace Gfx
           *
           * Contains graphics utility functions.
           */
           namespace Gfx
           {
               /**
               * Opens an image into an instance of sf::Image and slices each pair into its own texture block
               * and stores it in the last argument.
               *
               * @name Splice
               * @param const std::string& - The file path
               * @param const sf::IntRect* - The array of pairs
               * @param uint64_t - The number of pairs
               * @param sf::Texture*& - Reference to the container to store the items in.
               *
               */
                void Splice(const std::string&, const sf::IntRect*, uint64_t, sf::Texture*);

           }
    };
}

#endif // UTILITY_H
