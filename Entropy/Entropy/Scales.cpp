#include "Scales.h"
#include <string>
#include <fstream>
#include <sstream>

namespace entropy
{
    Scales parseScales( const String& filepath )
    {
        Scales output;
        String line;
        std::ifstream file( filepath );
        Int scaleCounter = 0;
        if ( file.is_open() )
        {
            while ( getline( file, line ) )
            {
                if ( line.substr( 0, 6 ) == "SCALE_" )
                {
                    std::stringstream sstr( line.substr( 6, 2 ) );
                    Int currentScaleNumber = 0;
                    sstr >> currentScaleNumber;
                    if ( currentScaleNumber == scaleCounter )
                    {
                        if ( line.substr( 8, 1 ) == " " )
                        {
                            String scaleString = line.substr( 9 );
                            Scale scale;
                            scale.parse( scaleString );
                            output.push_back( scale );
                            ++scaleCounter;
                        }
                        else
                        {
                            throw std::runtime_error("Error parsing scales file." );
                        }
                    }
                    else
                    {
                        throw std::runtime_error("Error parsing scales file." );
                    }
                }
                else
                {
                    throw std::runtime_error("Error parsing scales file." );
                }
            }
            file.close();
        }
        else
        {
            throw std::runtime_error("Error opening file." );
        }
        if ( output.size() != 13 )
        {
            throw std::runtime_error("Error parsing scales file." );
        }
        return output;
    }
}