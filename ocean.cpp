/*!************************************************************************
 * \file ocean.cpp
 * \author Hafiz
 * \par DP username: m.mohammadeffendi
 * \par Course: RSE1202
 * \par Programming Assignment 5
 * \date 16-2-2024
 * @brief Implementation of the Ocean class functions for a Battleship game.
 *
 * This source file contains the implementation of the functions required for the Battleship game,
 * including placing boats in the ocean, taking shots, updating game statistics, and printing the
 * physical representation of the ocean grid.
 * \return NIL.
 * 
 * \exception Nil
 *************************************************************************/

#include "ocean.h"
#include <iostream>
#include <iomanip>
#include <vector>

namespace HLP2{
namespace WarBoats{

// Constructor to create the ocean grid using x and y size and allocate memory for the ocean grid and for the array of boats to be placed in the ocean grid
    Ocean::Ocean(int num_boats, int x_size, int y_size) : grid{ new int[x_size * y_size]{} }, boats{ new Boat[num_boats]{} }, location{ x_size, y_size }, stats{} {}

    // Place boats into the ocean grid and update the boat stats in the ocean struct object.
    BoatPlacement Ocean::PlaceBoat(Boat const& boat) const
    {
        // Check if the boat is outside the ocean
        if (!IsValidCoordinate(boat.position)) { return BoatPlacement::bpREJECTED; }

        int start, end;

        // Orientation of the boat
        if (boat.orientation == oHORIZONTAL)
        {
            // Identifying the last possible horizontal space that the boat can cover in the ocean grid
            start = boat.position.x;
            // Identifying the maximum space of ocean grid (one-dimensional array)
            end = boat.position.x + BOAT_LENGTH;

            // Checking for out of bounds of the ocean grid, if it is, then reject
            if (end > location.x) { return BoatPlacement::bpREJECTED; }
        }
        else if (boat.orientation == oVERTICAL)
        {
            // Identifying the orientation of the boat
            start = boat.position.y;
            // Start identifying the last possible vertical space that the boat can cover in the ocean grid
            end = boat.position.y + BOAT_LENGTH;

            // Identifying the maximum space of ocean grid (one-dimensional array)
            if (end > location.y) { return BoatPlacement::bpREJECTED; }
        }
        else {
            // Checking for out of bounds of the ocean grid, if it is, then reject
            return BoatPlacement::bpREJECTED;
        }

        // Reject placement of the boat in that grid coordinates if that coordinates are occupied
        for (int i = start; i < end; ++i)
        {
            int gridIndex = (boat.orientation == oHORIZONTAL) ? i + boat.position.y * location.x : boat.position.x + i * location.x;
            if (grid[gridIndex] != DamageType::dtOK) { return BoatPlacement::bpREJECTED; }
        }

        // Place the boat in the ocean grid in the specified location
        for (int i = start; i < end; ++i)
        {
            int gridIndex = (boat.orientation == oHORIZONTAL) ? i + boat.position.y * location.x : boat.position.x + i * location.x;
            grid[gridIndex] = boat.ID;
        }

        // Identify and assign the current boat for this iteration
        boats[boat.ID - 1] = boat;
        // Identify and update the hit stats for the current boat for this iteration
        boats[boat.ID - 1].hits = 0;

        return BoatPlacement::bpACCEPTED;
    }

    // Identify stats of the shots fired in the ocean grid and update object in structure shotstats in structure ocean
    ShotResult Ocean::TakeShot(Point const& coordinate)
    {
        // Checking if the shot coordinates are within the range of ocean grid else return srILLEGAL
        if (!IsValidCoordinate(coordinate)) { return srILLEGAL; }

        // Calculate the location of where the boat is to be in the ocean grid
        int& position = grid[coordinate.x + coordinate.y * location.x];

        // Checking if that location was already occupied by a boat
        if (position == dtOK)
        {
            // Updating that location to be blown up
            position = dtBLOWNUP;
            // Updating missed stats
            stats.misses++;
            // Return miss
            return srMISS;
        }

        if (position > 0 && position < HIT_OFFSET)
        {
            int boatIndex = position - 1;
            // Increment boat hits
            boats[boatIndex].hits++;

            // Checking if all the sections of the boat are hit, and increment sunk in the ocean grid by updating the stats and return srSUNK
            if (boats[boatIndex].hits >= BOAT_LENGTH)
            {
                // Update sunk stats
                stats.sunk++;
                // Setting that the boat is hit at that coordinates
                position += HIT_OFFSET;
                // Update hit stats and return sunk
                stats.hits++;
                return srSUNK;
            }
            else
            {
                // Setting that the boat is hit at that coordinates
                position += HIT_OFFSET;
                // Update hit stats and return srHIT
                stats.hits++;
                return srHIT;
            }
        }

        // Update duplicates stats and return srDUPLICATE
        stats.duplicates++;
        return srDUPLICATE;
    }

    // Return all the stats (hits, sunk, misses, and duplicates) stored in the struct ShotStats in the struct ocean
    ShotStats Ocean::GetShotStats() const
    {
        return stats;
    }

    // Delete/free allocated memory for the ocean struct objects
    Ocean::~Ocean()
    {
        // Deallocate memory allocated for the ocean grid
        delete[] grid;
        // Deallocate memory allocated for the array of boats
        delete[] boats;
    }

    // Print the physical representation of the grid
void Ocean::Dump(int field_width, bool extraline, bool showboats) const
{
    int oceanWidth = location.x;
    int oceanHeight = location.y;

    // Each row
    for (int y = 0; y < oceanHeight; y++) {
        // Each column
        for (int x = 0; x < oceanWidth; x++)
        {
            // Value at x/y position
            int value = grid[y * oceanWidth + x];
            value = ((value > 0) && (value < HIT_OFFSET) && (!showboats)) ? 0 : value;
            std::cout << std::setw(field_width) << value;
        }

        std::cout << "\n";
        if (extraline) { std::cout << "\n"; }
    }
}

    // Assuming width and height are member variables
    Point Ocean::GetDimensions() const
    {
        return location;
    }

    // Assuming grid is a member variable of type int
    int const* Ocean::GetGrid() const
    {
        return grid;
    }

    // To check if coordinates are within the bounds of the grid
    bool Ocean::IsValidCoordinate(Point const& coordinate) const
    {
        return coordinate.x >= 0 && coordinate.x < location.x && coordinate.y >= 0 && coordinate.y < location.y;
    }


}
}
