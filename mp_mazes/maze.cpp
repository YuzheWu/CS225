/* Your code here! */
#include "maze.h"
#include <random>
#include <stdlib.h>
#include <queue>
#include <set>

SquareMaze::SquareMaze(){
}

void SquareMaze::makeMaze(int width, int height){
    _height = height;
    _width =  width;
    if(!walls.empty()){
        walls.clear();
    }
    DisjointSets maze;
    maze.addelements(width * height);
    std::vector<std::pair<bool, bool>> row;
    for(int i = 0; i < height; i++){
        walls.push_back(row);
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            walls[i].push_back(std::make_pair(true, true));
        }
    }
    std::vector<std::pair<int, int>> wall_cells;
    for (int i = 0; i < width * height - 1; i++){
        wall_cells.push_back(std::make_pair(i, 0));
        wall_cells.push_back(std::make_pair(i, 1));
    }

    int count = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(wall_cells.begin(), wall_cells.end(), g);
    for(size_t i = 0; i < wall_cells.size(); i++){
        if (count == width * height - 1)
            break;
        int idx = wall_cells[i].first;
        int dir = wall_cells[i].second;
        int x = idx % width;
        int y = idx / width;

        if (dir == 0 && x != width-1) {
            if (maze.find(idx) != maze.find(idx+1)) {
                walls[y][x].second = false;
                maze.setunion(idx, idx + 1);
                count++;
            }
        }
        else if (dir == 1 && y != height - 1) {
            if(maze.find(idx) != maze.find(idx + width)){
                walls[y][x].first = false;
                maze.setunion(idx, idx + width);
                count++;
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    std::pair<bool, bool> wall = walls[y][x];
    if(dir == 1){
        return !wall.first;
    } else if(dir == 0){
        return !wall.second;
    } else if(dir == 2){
        if(x == 0){
            return false;
        }
        std::pair<bool, bool> left_wall = walls[y][x - 1];
        return !left_wall.second;
    } else{
        if(y == 0){
            return false;
        }
        std::pair<bool, bool> up_wall = walls[y - 1][x];
        return !up_wall.first;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        walls[y][x].second = exists;
    }else{
        walls[y][x].first = exists;
    }
}

std::vector<int> SquareMaze::solveMaze(){
    std::vector< int > distance( _width*_height, -1 );
	std::vector< int > previous( _width*_height, -1 );
	std::queue< int > Q;

	// Push all cells/vertices into the Queue
	Q.push(0);

	// Distance from source to source = 0
	distance[ 0 ] = 0;

	// Nodes that are unoptimized are in the queue
	while ( !Q.empty() )
	{
		// Remove the vertex with the smallest distance
		int u = Q.front();
		Q.pop();

		// For each neighbor of u, calculate distance to source
		std::vector< int > neighbors;
		neighbors.clear();
		int x = u % _width;
		int y = u / _width;
		if ( canTravel( x, y, 0 ) )
		{
			neighbors.push_back( _width * y + x + 1 );
		}
		if ( canTravel( x, y, 1 ) )
		{
			neighbors.push_back( _width * (y+1) + x );
		}
		if ( canTravel( x, y, 2 ) )
		{
			neighbors.push_back( x-1 + y * _width );
		}
		if ( canTravel( x, y, 3 ) )
		{
			neighbors.push_back( x + _width*(y-1) );
		}

		for ( size_t i = 0; i < neighbors.size(); i++ )
		{
			int alt = distance[ u ] + 1;
		if ( distance[ neighbors[ i ] ] == -1 )
			{
				distance[ neighbors[i] ] = alt;
				previous[ neighbors[i] ] = u;
                Q.push(neighbors[i]);
			}
		}
	}

	// Find the vertex along the bottom with the longest distance to source
	int maxDistance = 0;
	int maxDistanceVertex = 0;
	for ( int i = _width * (_height-1); i < _width * _height; i++ )
	{
		if ( distance[i] > maxDistance )
		{
			maxDistance = distance[i];
			maxDistanceVertex = i;
		}
	}

	// Store in reverse the directions from source to target
	std::vector< int > directions;

	int v = maxDistanceVertex;
	int curr = previous[ v ];
	while ( curr != -1 )
	{
		if ( curr + 1 == v )
		{
			directions.push_back( 0 );
		}
		else if ( curr + _width == v  )
		{
			directions.push_back( 1 );
		}
		else if ( curr - 1 == v )
		{
			directions.push_back( 2 );
		}
		else if ( curr - _width == v  )
		{
			directions.push_back( 3 );
		}
		v = curr;
		curr = previous[ curr ];
	}

	// Reverse the directions for the final set of directions
	std::reverse( directions.begin(), directions.end() );

	return directions;
}

PNG * SquareMaze::drawMaze()const{
    PNG * result = new PNG (_width * 10 + 1, _height * 10 + 1);
    HSLAPixel blackPixel(0, 0, 0);
    for(unsigned int x = 10; x < result->width(); x++){
        result->getPixel(x, 0) = blackPixel;
    }
    for(unsigned int y = 0; y < result->height(); y++){
        result->getPixel(0, y) = blackPixel;
    }
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            std::pair<bool, bool> wall = walls[y][x];
            if(wall.first){
                for(int k = 0; k <= 10; k++){
                    result->getPixel(x * 10 + k, (y + 1) * 10) = blackPixel;
                }
            }
            if(wall.second){
                for(int k = 0; k <= 10; k++){
                    result->getPixel((x + 1) * 10, y * 10 + k) = blackPixel;
                }
            }
        }
    }
    return result;
}

PNG * SquareMaze::drawMazeWithSolution(){
    PNG *result = drawMaze();
    std::vector<int> solpath = solveMaze();
    HSLAPixel redPixel(0, 1, 0.5, 1);
    HSLAPixel whitePixel(0, 0 ,1);
    int x = 5;
    int y = 5;
    for(int& dir : solpath){
        if(dir == 0){
            for(int i = x; i <= x + 10; i++){
                result->getPixel(i, y) = redPixel;
            }
            x = x + 10;
        }
        if(dir == 1){
            for(int i = y; i <= y + 10; i++){
                result->getPixel(x, i) = redPixel;
            }
            y = y + 10;
        }
        if(dir == 2){
            for(int i = x; i >= x - 10; i--){
                result->getPixel(i, y) = redPixel;
            }
            x = x - 10;
        }
        if(dir == 3){
            for(int i = y; i >= y - 10; i--){
                result->getPixel(x, i) = redPixel;
            }
            y = y - 10;
        }
    }
    for(int i = x - 4; i <= x + 4; i++){
        result->getPixel(i, y + 5) = whitePixel;
    }
    return result;
}
