// C++ Implementation of Quad Tree
#include <iostream>
#include <math.h>

#include "headers/quadtree.h"
#include "headers/joueur.h"

using namespace std;
  

  

// Insert a node into the quadtree
void Quad::insert(Plateforme *node)
{


    if (node == NULL)
        return;
  

    // Current quad cannot contain it
    if (!inBoundary((*node).x, (*node).y)){
    
        return;
    }
              
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if (abs(topLeft.x - botRight.x) <= 1 &&
        abs(topLeft.y - botRight.y) <= 1)
    {
        if (n == NULL)
            n = node;
        return;
    }
  
    if ((topLeft.x + botRight.x) / 2 >= node->x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->y)
        {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }
  
        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                        (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                        botRight.y));
            botLeftTree->insert(node);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= node->y)
        {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        topLeft.y),
                    Point(botRight.x,
                        (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }
  
        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}
  
// Find a node in a quadtree
Plateforme* Quad::search(Point p)
{
    // Current quad cannot contain it
    if (!inBoundary(p.x, p.y)){
        
        return NULL;
    }



    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (n != NULL){
        return n;
      }
      
    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }
  
        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }
  
        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
};
  
// Check if current quadtree contains the point
bool Quad::inBoundary(float x, float y)
{
    return (x >= topLeft.x &&
        x <= botRight.x &&
        y >= topLeft.y &&
        y <= botRight.y);

}