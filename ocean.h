/*!************************************************************************
 * \file ocean.hpp
 * \author Hafiz
 * \par DP username: m.mohammadeffendi
 * \par Course: RSE1202
 * \par Programming Assignment 5
 * \date 16-2-2024
 * @brief Declarations of the Ocean class functions for a Battleship game.
 *
 * This source file contains the declarations of the functions required for the Battleship game,
 * including placing boats in the ocean, taking shots, updating game statistics, and printing the
 * physical representation of the ocean grid.
 * \return NIL.
 * 
 * \exception Nil
 *************************************************************************/


#ifndef OCEAN_H
#define OCEAN_H

#include <iostream>
#include <iomanip>
#include <vector>

namespace HLP2 {
namespace WarBoats {

     /**
     * @brief Length of a boat.
     */
    inline int const BOAT_LENGTH {4};

    /**
     * @brief Value added to the boat ID.
     */
    inline int const HIT_OFFSET {100};

    /**
     * @brief Enumeration for boat orientation.
     */
    enum Orientation   { oHORIZONTAL, oVERTICAL };

    /**
     * @brief Enumeration for shot results.
     */
    enum ShotResult    { srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL };

    /**
     * @brief Enumeration for damage types.
     */
    enum DamageType    { dtOK = 0, dtBLOWNUP = -1 };

    /**
     * @brief Enumeration for boat placement.
     */
    enum BoatPlacement { bpACCEPTED, bpREJECTED };

    /**
     * @brief Represents a coordinate in the Ocean.
     */
    struct Point
    {
        int x;  //!< X-coordinate
        int y;  //!< Y-coordinate
    };

    /**
     * @brief Represents a Boat in the Ocean.
     */
    struct Boat
    {
        int hits;                //!< Hits taken
        int ID;                  //!< Unique ID
        Orientation orientation; //!< Horizontal/Vertical
        Point position;          //!< X-Y coordinate
    };

    /**
     * @brief Represents statistics of the game.
     */
    struct ShotStats
    {
        int hits;       //!< The number of boat hits
        int misses;     //!< The number of boat misses
        int duplicates; //!< The number of duplicate hits
        int sunk;       //!< The number of boats sunk
    };

    /**
     * @brief The Ocean class represents the attributes and functions of the game ocean.
     */
    class Ocean
    {
    public:
        /**
         * @brief Constructor for the Ocean class.
         * @param num_boats Number of boats in the ocean.
         * @param x_size Ocean size along the x-axis.
         * @param y_size Ocean size along the y-axis.
         */
        Ocean(int num_boats, int x_size, int y_size);

        /**
         * @brief Destructor for the Ocean class.
         */
        ~Ocean();

        /**
         * @brief Takes a shot at the specified coordinate.
         * @param coordinate The target coordinate for the shot.
         * @return Result of the shot.
         */
        ShotResult TakeShot(Point const& coordinate);

        /**
         * @brief Places a boat in the ocean.
         * @param boat The boat to be placed.
         * @return Result of the boat placement.
         */
        BoatPlacement PlaceBoat(Boat const& boat) const;

        /**
         * @brief Gets the shot statistics.
         * @return Shot statistics of the game.
         */
        ShotStats GetShotStats() const;

        /**
         * @brief Prints the physical representation of the ocean grid.
         * @param field_width Width of each grid field.
         * @param extraline Flag to print an extra line between rows.
         * @param showboats Flag to display boats in the grid.
         */
        void Dump(int field_width = 4, bool extraline = false, bool showboats = true) const;

        /**
         * @brief Gets the dimensions of the ocean grid.
         * @return Point representing the dimensions (width and height) of the ocean grid.
         */
        Point GetDimensions() const;

        /**
         * @brief Gets the pointer to the ocean grid.
         * @return Pointer to the ocean grid.
         */
        int const* GetGrid() const;

        /**
         * @brief Checks if a coordinate is valid within the ocean grid boundaries.
         * @param coordinate The coordinate to be checked.
         * @return True if the coordinate is valid, false otherwise.
         */
        bool IsValidCoordinate(Point const& coordinate) const;

    private:
        int  *grid;         //!< The 2D ocean grid.
        int num_boats;      //!< Number of boats in the ocean.
        int x_size;         //!< Ocean size along the x-axis.
        int y_size;         //!< Ocean size along the y-axis.
        Boat *boats;        //!< Array of boat information.
        Point location;     //!< Dimensions of the ocean grid.
        ShotStats stats;    //!< Statistics of the game.

    };

}
}

#endif