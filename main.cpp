#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "headers/Tile.h"
#include "headers/WaveFunctionCollapse.h"

void setNeighbors(std::vector<std::vector<Tile>>& tiles)
{
   for(int i = 0; i < tiles.size(); ++i)
   {
      for(int j = 0; j < tiles[i].size(); ++j)
      {
         if(i != 0) // Top neighbor exists
            tiles[i][j].setTopNeighborColor(tiles[i-1][j].getColor());
         if(i != tiles.size()-1) // Bottom neighbor exists
            tiles[i][j].setBottomNeighborColor(tiles[i+1][j].getColor());
         if(j != 0) // Left neighbor exists
            tiles[i][j].setLeftNeighborColor(tiles[i][j-1].getColor());
         if(j != tiles[i].size()-1) // Right neighbor exists
            tiles[i][j].setRightNeighborColor(tiles[i][j+1].getColor());
      }
   }
}

std::vector<std::vector<Tile>> customTiles(std::vector<sf::Color>& colors)
{
   // INPUT CUSOM COLORS HERE //
   std::vector<std::vector<unsigned>> tileColors = {
    // Template 1
    
    {1, 1, 1, 1},
    {1, 1, 2, 2},
    {1, 2, 2, 0},
    {1, 2, 0, 0},
    {1, 2, 0, 0}
    
    // Template 2; NOT WORKING
    /*
    {1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 1},
    {1, 2, 0, 0, 2, 1},
    {1, 2, 0, 0, 2, 1},
    {1, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1}
    */
    // Example 3
    /*
    {0, 2, 0},
    {2, 1, 2},
    {0, 2, 0}
    */
   };
   //------------------------//

   std::vector<std::vector<Tile>> tiles;
   for(int i = 0; i < tileColors.size(); ++i)
   {
      std::vector<Tile> row;
     for(int j = 0; j < tileColors[i].size(); ++j)
      {
         Tile tile(colors[tileColors[i][j]]);
         tile.setPosition(j*5, i*5);
         row.push_back(tile);
      }
      tiles.push_back(row);
   }

   setNeighbors(tiles);
   return tiles;
}

int main()
{
   const unsigned WIDTH = 200, HEIGHT = 200;
   sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Wave Function Collapse");

   srand(time(NULL));

   std::vector<sf::Color> colors;
   colors.push_back(sf::Color::Green);
   colors.push_back(sf::Color::Blue);
   colors.push_back(sf::Color::Yellow);

   std::vector<std::vector<Tile>> tiles = customTiles(colors);

   WaveFunctionCollapse wfc(tiles, colors, 15, 15);
   std::vector<std::vector<Tile>> generatedTiles = wfc.generateTileSet();

   while(window.isOpen())
   {
      sf::Event event;
      while(window.pollEvent(event))
      {
         if(event.type == sf::Event::Closed)
         {
            window.close();
         }
      }

      window.clear();

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      {
         for(int i = 0; i < tiles.size(); ++i)
            for(int j = 0; j < tiles[i].size(); ++j)
               window.draw(tiles[i][j].getTile());
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      {
         for(int i = 0; i < generatedTiles.size(); ++i)
            for(int j = 0; j < generatedTiles[i].size(); ++j)
               window.draw(generatedTiles[i][j].getTile());
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      {
         generatedTiles = wfc.generateTileSet();
      }

      window.display();
      
   }
   return 0;
}
