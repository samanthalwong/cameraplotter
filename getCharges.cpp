#include </raid/romulus/swong/VBF/VBF/VBankFileReader.h>
#include </raid/romulus/swong/VBF/VBF/VBankFileWriter.h>
#include </raid/romulus/swong/VBF/VBF/VPacket.h>
#include </raid/romulus/swong/VBF/VBF/VArrayEvent.h>
#include </raid/romulus/swong/VBF/VBF/VDatum.h>
#include </raid/romulus/swong/VBF/VBF/VConfigMaskUtil.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

// declare that we're using the VConfigMaskUtil namespace, which gives us
// easy access to parseConfigMask().
using namespace VConfigMaskUtil;
vector< unsigned> events;

int main(int argc, char *argv[]){
	string run = argv[1];
	const char *ev = argv[2];
	
	vector<string> events = split(ev,',');
	vector<VPacket*> packets;

	// read in file
	VBankFileReader* reader = NULL;
	std::string fVBFFileName= run;
	reader = new VBankFileReader(fVBFFileName);
	vector< bool > configMask=reader->getConfigMask();

	// output file
	std::ofstream outFile;
	outFile.open("charges.txt");

	//if (events.size == 0) cout << "ERROR: NO EVENTS GIVEN";
	if (events.size() == 1){
		if (events[0].compare("all") == 0){
			unsigned npacks = reader->numPackets()-1;
			for (unsigned i=0; i<npacks; i++){
				packets.push_back(reader->readPacket(i));
			}
		}
		else{
			int e = atoi(ev);
			packets.push_back(reader->readPacket((unsigned)e));
		}
	}
	else{
		for (unsigned i=0; i<events.size(); i++){
			packets.push_back(reader->readPacket(i));
		}
	}
	
	for (int i=0; i<packets.size(); i++){

		if (packets[i]->hasArrayEvent()) {
			VArrayEvent *ae=packets[i]->getArrayEvent();
			unsigned long evNum = ae->getEventNumber();
			outFile << evNum << " ";
			for(unsigned j=0;j<4;j++){ //loop through each telescope
				VEvent *event = ae->getEvent(j);
				if (event == 0){
					continue;
				}
				uword16 channels = event->getMaxNumChannels();
				unsigned numchannels = (unsigned)channels;

				for (unsigned k=0; k<numchannels; k++){
					uword16 charge = event->getCharge(k);
					outFile << charge << ",";
				}
				outFile << " ";
			}
			outFile << endl;
		}
	}
		
	outFile.close();	
	return 0;
}
