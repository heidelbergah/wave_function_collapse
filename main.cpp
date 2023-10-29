#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "headers/Tile.h"
#include "headers/WaveFunctionCollapse.h"

// Sometimes crashes because first collapse makes a plus shaped 0 entropy pattern

void setNeighbors(std::vector<std::vector<Tile>>& tiles, unsigned h = 200, unsigned w = 200)
{
   unsigned tileHeight = tiles[0][0].getHeight(), tileWidth = tiles[0][0].getWidth();
   for(int i = 0; i < h; i+=tileHeight)
   {
      for(int j = 0; j < w; j+=tileWidth)
      {
         int iIndex = i/tileHeight, jIndex = j/tileWidth;
         if(iIndex != 0) // Top neighbor exists
            tiles[iIndex][jIndex].setTopNeighborColor(tiles[iIndex-1][jIndex].getColor());
         if(iIndex != (h/tileHeight)-1) // Bottom neighbor exists
            tiles[iIndex][jIndex].setBottomNeighborColor(tiles[iIndex+1][jIndex].getColor());
         if(jIndex != 0) // Left neighbor exists
            tiles[iIndex][jIndex].setLeftNeighborColor(tiles[iIndex][jIndex-1].getColor());
         if(jIndex != (w/tileWidth)-1) // Right neighbor exists
            tiles[iIndex][jIndex].setRightNeighborColor(tiles[iIndex][jIndex+1].getColor());
      }
   }
}

std::vector<std::vector<Tile>> randomTiles(std::vector<sf::Color>& colors, unsigned HEIGHT = 200, unsigned WIDTH = 200)
{
   std::vector<std::vector<Tile>> tiles;
   for(int i = 0; i < HEIGHT; i+=5)
   {
      std::vector<Tile> row;
      for(int j = 0; j < WIDTH; j+=5)
      {
         int randomColorIndex = rand() % colors.size();
         Tile tile(colors[randomColorIndex]);
         tile.setPosition(j, i);
         row.push_back(tile);
      }
      tiles.push_back(row);
   }

   setNeighbors(tiles);
   return tiles;
}

std::vector<std::vector<Tile>> customTiles(std::vector<sf::Color>& colors)
{
   // INPUT CUSOM COLORS HERE //
   std::vector<std::vector<unsigned>> tileColors = {
    {3, 3, 3, 3},
    {3, 3, 4, 4},
    {3, 4, 4, 2},
    {3, 4, 2, 2},
    {3, 4, 2, 2}
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

   setNeighbors(tiles, tiles.size()*5, tiles[0].size()*5);
   return tiles;
}

int main()
{
   const unsigned WIDTH = 200, HEIGHT = 200;
   sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Wave Function Collapse");

   srand(time(NULL));

   std::vector<sf::Color> colors;
   colors.push_back(sf::Color::White);
   colors.push_back(sf::Color::Black);
   colors.push_back(sf::Color::Green);
   colors.push_back(sf::Color::Blue);
   colors.push_back(sf::Color::Yellow);

   std::vector<std::vector<Tile>> tiles = customTiles(colors);

   WaveFunctionCollapse wfc(tiles, colors, 10, 12);
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
      /*
      for(int i = 0; i < tiles.size(); ++i)
         for(int j = 0; j < tiles[i].size(); ++j)
            window.draw(tiles[i][j].getTile());
      */
      for(int i = 0; i < generatedTiles.size(); ++i)
         for(int j = 0; j < generatedTiles[i].size(); ++j)
            window.draw(generatedTiles[i][j].getTile());

      window.display();
      
   }
   return 0;
}
