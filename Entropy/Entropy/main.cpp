#include <iostream>
#include "args.h"
#include "Numbers.h"
#include "Scales.h"
#include "Config.h"
#include "MxSetup.h"
#include <fstream>
#include "Test/cpulRun.h"
#include "mainSandbox.h"
#include "Quantizer.h"
#include "equanta.h"

int main(int argc, const char * argv[])
{
    using namespace std;
    using namespace entropy;

    /* begin execution time clock */
    auto t0=clock();
    
    /* run unit tests */
    cpulRun( true );
    
    /* input file paths */
    String fpInput;
    String fpConfig;
    String fpScales;
    
    /* parse the args (if any), abort if arg parsing function returns false */
    if ( ! args( argc, argv, fpInput, fpConfig, fpScales ) ) { return -1; }
    
    /* parse the files */
    Numbers data = Numbers::parse( fpInput );
    Scales scales = parseScales( fpScales );
    Config config = parseConfig( fpConfig );
    
    /* Create Instrument List */
    auto instrumentList = createInstrumentList( config );
    
    /* set-up MusicXML document */
    auto doc = createMxDocument( config, instrumentList );
    
    /* Convert Numbers to Entropy Quanta */
    auto quanta = equanta( data, config.getMeasureCount() );
    
    /* do stuff */
    mainSandbox( doc, config, quanta, scales, instrumentList );
    
    /* write the MusicXML document to disk */
    ofstream myfile;
    myfile.open ( config.getTitle()+".xml" );
    doc->toStream( myfile );
    myfile.close();
    
    /* calculate execution time */
    auto t1=clock();
    double perSec = (double)CLOCKS_PER_SEC;
    std::cout << "Execution time: " << (((double)(t1-t0))/perSec) << " seconds." << std::endl;
    
    /* end the program */
    return 0;
}

