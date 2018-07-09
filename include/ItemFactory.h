#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <string>
#include <vector>

class ItemFactory {
public:
    static void Load(std::vector<std::string> file_paths);
};

#endif /* ITEMFACTORY_H */
