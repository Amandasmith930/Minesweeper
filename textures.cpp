//
// Created by Admin on 4/4/22.
//

#include "textures.h"

unordered_map<string, sf::Texture> Textures :: text;

void Textures:: LoadText(string file){
    string path = "images/";
    path += file + ".png";

    text[file].loadFromFile(path);
}

sf:: Texture& Textures:: GetTexture(string textureName){
    if (text.find(textureName) == text.end()) {
        LoadText(textureName);
    }
        return text[textureName];

}
void Textures:: Clear(){
    text.clear();
}