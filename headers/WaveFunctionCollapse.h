/*
 * James Bouchat
 * 10-23-2023
 * WaveFunctionCollapse.h
 */

#ifndef WAVE_FUNCTION_COLLAPSE_H
#define WAVE_FUNCTION_COLLAPSE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include "Tile.h"

class WaveFunctionCollapse
{
private:
   unsigned WIDTH, HEIGHT;
   std::vector<std::vector<Tile>>& tiles;
   std::vector<sf::Color>& colors;
   std::vector<std::vector<Tile>> generatedTiles;
   std::vector<std::vector<std::vector<sf::Color>>> entropy;
   std::vector<std::vector<std::vector<sf::Color>>> ruleset; // INDEXING [color][side][otherColor]
                                                             // [color] index of color
                                                             // [side] 0 for top, 1 for right, etc.
                                                             // [otherColor] what color exists there

   void generateRuleSet()
   {
      // CLEAR RULESET 
      for(unsigned i = 0; i < tiles.size(); ++i)
      {
         for(unsigned j = 0; j < tiles[i].size(); ++j) 
         {
            // Grab color index of tile
            unsigned currentColorIndex;
            for(unsigned colorIndex = 0; colorIndex < colors.size(); ++colorIndex)
            {
               if(colors[colorIndex] == tiles[i][j].getColor())
               {
                  currentColorIndex = colorIndex;
                  break;
               }
            }

            if(i != 0) // Top neighbor exists
            {
               if(!isColorAccountedFor(*tiles[i][j].getTopNeighborColor(), currentColorIndex, 0))
               {
                  ruleset[currentColorIndex][0].push_back(*tiles[i][j].getTopNeighborColor());
               }
            }
            if(i != tiles.size()-1) // Bottom neighbor exists
            {
               if(!isColorAccountedFor(*tiles[i][j].getBottomNeighborColor(), currentColorIndex, 2))
               {
                  ruleset[currentColorIndex][2].push_back(*tiles[i][j].getBottomNeighborColor());
               }
            }
            if(j != 0) // Left neighbor exists
            {
               if(!isColorAccountedFor(*tiles[i][j].getLeftNeighborColor(), currentColorIndex, 3))
               {
                  ruleset[currentColorIndex][3].push_back(*tiles[i][j].getLeftNeighborColor());
               }
            }
            if(j != tiles[i].size()-1) // Right neighbor exists
            {
               if(!isColorAccountedFor(*tiles[i][j].getRightNeighborColor(), currentColorIndex, 1))
               {
                  ruleset[currentColorIndex][1].push_back(*tiles[i][j].getRightNeighborColor());
               }
            }
         }
      }
   }

   void collapse(unsigned i, unsigned j)
   {
      unsigned possibilities = entropy[i][j].size();
      unsigned entropyIndex = rand() % possibilities;
      generatedTiles[i][j].setColor(entropy[i][j][entropyIndex]);
      generatedTiles[i][j].setPosition(i*5, j*5);
      setNeighboringEntropy(i, j, entropyIndex);
      std::cout << "SET_NEIGHBORING_ENTROPY RUNS" << std::endl;
      entropy[i][j].clear();
   }

   void setStartingEntropy()
   {
      for(unsigned i = 0; i < HEIGHT; ++i)
         for(unsigned j = 0; j < WIDTH; ++j)
            for(unsigned colorIndex = 0; colorIndex < colors.size(); ++colorIndex)
               entropy[i][j].push_back(colors[colorIndex]);
   }

   void setNeighboringEntropy(unsigned i, unsigned j, unsigned entropyIndex)
   {
      unsigned colorIndex = getColorIndex(i, j, entropyIndex);
      if(i != 0) // Top neighbor exists
         reduceEntropy(i-1, j, colorIndex, 0);
      if(i != generatedTiles.size()-1) // Bottom neighbor exists
         reduceEntropy(i+1, j, colorIndex, 2);
      if(j != 0) // Left neighbor exists
         reduceEntropy(i, j-1, colorIndex, 3);
      if(j != generatedTiles[i].size()-1) // Right neighbor exists
         reduceEntropy(i, j+1, colorIndex, 1);
   }

   void reduceEntropy(unsigned i, unsigned j, unsigned colorIndex, unsigned side)
   {
      std::vector<sf::Color> validColors;
      for(unsigned entropyIndex = 0; entropyIndex < entropy[i][j].size(); ++entropyIndex)
      {
         for(unsigned rulesetIndex = 0; rulesetIndex < ruleset[colorIndex][side].size(); ++rulesetIndex)
         {
            sf::Color entropyColor = entropy[i][j][entropyIndex];
            sf::Color rulesetColor = ruleset[colorIndex][side][rulesetIndex];
            if(entropyColor == rulesetColor)
            {
               validColors.push_back(entropyColor);
            }
         }
      }
      entropy[i][j] = validColors;
   
   }

   bool isColorAccountedFor(sf::Color color, unsigned colorIndex, unsigned side)
   {
      for(unsigned i = 0; i < ruleset[colorIndex][side].size(); ++i)
         if(ruleset[colorIndex][side][i] == color)
            return true;
      return false;
   }

   int getColorIndex(unsigned i, unsigned j, unsigned entropyIndex)
   {
      sf::Color color = entropy[i][j][entropyIndex];
      for(int colorIndex = 0; colorIndex < colors.size(); ++colorIndex)
         if(color == colors[colorIndex])
            return colorIndex;
      return -1;
   }

   void printEntropy()
   {
      for(int i = 0; i < HEIGHT; ++i)
      {
         for(int j = 0; j < WIDTH; ++j)
         {
            std::cout << entropy[i][j].size() << "\t";
         }
         std::cout << std::endl;
      }
   }
public:
   // Constructor
   WaveFunctionCollapse(std::vector<std::vector<Tile>>& t, std::vector<sf::Color>& c, unsigned WIDTH, unsigned HEIGHT)
   : tiles(t),
     colors(c),
     ruleset(c.size(), std::vector<std::vector<sf::Color>>(4)),
     entropy(HEIGHT, std::vector<std::vector<sf::Color>>(WIDTH)),
     generatedTiles(HEIGHT, std::vector<Tile>(WIDTH, Tile(sf::Color::Black)))
   {
      this->WIDTH = WIDTH;
      this->HEIGHT = HEIGHT;
   }

   // Getters & Setters
   void setTiles(std::vector<std::vector<Tile>>& t)
   {
      tiles = t;
   }

   void setColors(std::vector<sf::Color>& c)
   {
      colors = c;
   }

   std::vector<std::vector<Tile>>& getTiles()
   {
      return tiles;
   }

   std::vector<sf::Color>& getColors()
   {
      return colors;
   }

   // Methods
   std::vector<std::vector<Tile>>& generateTileSet()
   {
      std::vector<std::vector<Tile>> t(HEIGHT, std::vector<Tile>(WIDTH, Tile(sf::Color::Black)));
      generateRuleSet();
      std::cout << "RULESET RUNS" << std::endl;
      setStartingEntropy();
      std::cout << "SET_STARTING_ENTROPY RUNS" << std::endl;
      unsigned lowestEntropy;
      unsigned startingIndexI = rand() % tiles.size();
      unsigned startingIndexJ = rand() % tiles[0].size();
      collapse(startingIndexI, startingIndexJ);
      std::cout << "COLLAPSE RUNS" << std::endl;
      printEntropy();
      unsigned iteration = 1;
      while(iteration <= (HEIGHT*WIDTH)-1)
      {
         unsigned minEntropy = colors.size();
         unsigned minI, minJ;
         for(unsigned i = 0; i < HEIGHT; ++i)
         {
            for(unsigned j = 0; j < WIDTH; ++j)
            {
               if(entropy[i][j].size() != 0)
               {
                  if(entropy[i][j].size() < minEntropy)
                  {
                     minEntropy = entropy[i][j].size();
                     minI = i;
                     minJ = j;
                  }
               }
            }
         }
         collapse(minI, minJ);
         ++iteration;
         std::cout << iteration << ": COLLAPSE RUNS" << std::endl; 
         printEntropy();
      }
      return generatedTiles;
   }
};

#endif
