// testfile for the doq parser

#include "DOQParser/DOQParser.h"
#include <iostream.h>
#include <iomanip.h>
#include <string>


int main (int argc, char* argv[])
{
  int filecount;
  DOQParser* foo;
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " geoDOQfilelist" << endl;
    exit(666);
  }

  for (filecount = 1; filecount < argc; filecount++)
  {
    foo = new DOQParser(argv[filecount]);
    if (!foo->good())
    {
      cerr << "Error opening DOQ " << argv[filecount] << endl;
      cerr << "Skipping..." << endl;
      delete foo;
      continue;
    }

    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "FILENAME: " << argv[filecount] << endl;
    string* name = foo->getQuadName();
    if (name != NULL)
    {
      cout << "Name: " << *name << endl; delete name;
    }
    string* quad = foo->getQuadrant();
    if (quad != NULL)
    {
      cout << "Quad: " << *quad << endl; delete quad;
    }
    cout << "West Hour: " << foo->getWestHour() << endl;
    cout << "West Minute: " << foo->getWestMinute() << endl;
    cout << "West Second:" << foo->getWestSecond() << endl;
    cout << "East Hour: " << foo->getEastHour() << endl;
    cout << "East Minute: " << foo->getEastMinute() << endl;
    cout << "East Second: " << foo->getEastSecond() << endl;
    cout << "North Hour: " << foo->getNorthHour() << endl;
    cout << "North Minute: " << foo->getNorthMinute() << endl;
    cout << "North Second: " << foo->getNorthSecond() << endl;
    cout << "South Hour: " << foo->getSouthHour() << endl;
    cout << "South Minute: " << foo->getSouthMinute() << endl;
    cout << "South Second: " << foo->getSouthSecond() << endl;
    string* tdate = foo->getProdDate();
    if (tdate != NULL)
    {
      cout << "Prod Date: " << *tdate << endl; delete tdate;
    } 
    string* rasterOrder = foo->getRasterOrder();
    if (rasterOrder != NULL)
    {
      cout << "Raster Order: " << *rasterOrder << endl; delete rasterOrder;
    }
    string* bandOrg = foo->getBandOrganization();
    if (bandOrg != NULL)
    {
      cout << "Band Organization: " << *bandOrg << endl; delete bandOrg;
    }
    for (int bcount = 0; bcount <= 2; bcount++)
    {
      string* bandContent = foo->getBandContent(bcount);
      if (bandContent != NULL)
      {
	cout << "Band Content: " << *bandContent << endl; delete bandContent;
      }
      delete bandContent;
    }
    cout << "BPS: " << foo->getBitsPerPixel() << endl;
    cout << "Samples: " << foo->getSamples() << endl;
    cout << "Lines: " << foo->getLines() << endl;
    string* datum = foo->getHorizontalDatum();
    if (datum != NULL)
    {
      cout << "Horizontal Datum: " << *datum << endl; delete datum;
    }
    string* tsystem = foo->getHorizontalCoordinateSystem();
    if (tsystem != NULL)
    {
      cout << "Coordinate System: " << *tsystem << endl; delete tsystem;
    }
    cout << "Coordinate Zone: " << foo->getCoordinateZone() << endl;
    string* units = foo->getHorizontalUnits();
    if (units != NULL)
    {
      cout << "Units: " << *units << endl; delete units;
    }
    cout << "Horizontal Resolution: " << foo->getHorizontalResolution() << endl;
    string* secdatum = foo->getSecondaryHorizontalDatum();
    if (secdatum != NULL)
    {
      cout << "Sec Horiz Datum: " << *secdatum << endl; delete secdatum;
    }
    cout << "X: " << foo->getXOrigin() << endl;
    cout << "Y: " << foo->getYOrigin() << endl;
    cout << "Sec X: " << foo->getSecondaryXOrigin() << endl;
    cout << "Sec Y: " << foo->getSecondaryYOrigin() << endl;
    int numNations = foo->getNumNations();
    cout << "Num Nations: " << numNations << endl;
    for (int _foocount = 1; _foocount <= numNations; _foocount++)
    {
      string* nation = foo->getNation(_foocount);
      if (nation != NULL)
      {
	cout << "Nation(" << _foocount << "): " << *nation << endl; delete nation;
      }
    }
    int numStates = foo->getNumStates();
    cout << "Num States: " << foo->getNumStates() << endl;
    for (int _foocount = 1; _foocount <= numStates; _foocount++)
    {
      string* state = foo->getState(_foocount);
      if (state != NULL)
      {
	cout << "State(" << _foocount << "): " << *state << endl; delete state;
      }
    }
    cout << "NWX: " << foo->getNWQuadX() << endl;
    cout << "NWY: " << foo->getNWQuadY() << endl;
    cout << "NEX: " << foo->getNEQuadX() << endl;
    cout << "NEY: " << foo->getNEQuadY() << endl;
    cout << "SEX: " << foo->getSEQuadX() << endl;
    cout << "SEY: " << foo->getSEQuadY() << endl;
    cout << "SWX: " << foo->getSWQuadX() << endl;
    cout << "SWY: " << foo->getSWQuadY() << endl;
    cout << "SNWX: " << foo->getSecNWQuadX() << endl;
    cout << "SNWY: " << foo->getSecNWQuadY() << endl;
    cout << "SNEX: " << foo->getSecNEQuadX() << endl;
    cout << "SNEY: " << foo->getSecNEQuadY() << endl;
    cout << "SSEX: " << foo->getSecSEQuadX() << endl;
    cout << "SSEY: " << foo->getSecSEQuadY() << endl;
    cout << "SSWX: " << foo->getSecSWQuadX() << endl;
    cout << "SSWY: " << foo->getSecSWQuadY() << endl;
    cout << "RMSE: " << foo->getRMSE() << endl;
    string* source = foo->getImageSource();
    if (source != NULL)
    {
      cout << "Image Source: " << *source << endl; delete source;
    }
    cout << "Num Sources: " << foo->getNumImageSources() << endl;
    string* id = foo->getSourceImageID(1);
    if (id != NULL)
    {
      cout << "SourceImageID: " << *id << endl; delete id;
    }
    string* date = foo->getSourceImageDate(1);
    if (date != NULL)
    {
      cout << "Source Image Date: " << *date << endl; delete date;
    }
    string* dem = foo->getSourceDEMDate();
    if (dem != NULL)
    {
      cout << "DEM Date: " << *dem << endl; delete dem;
    }
    string* agency = foo->getAgency();
    if (agency != NULL)
    {
      cout << "Agency: " << *agency << endl; delete agency;
    }
    string* producer = foo->getProducer();
    if (producer != NULL)
    {
      cout << "Producer: " << *producer << endl; delete producer;
    }
    string* system = foo->getProductionSystem();
    if (system != NULL)
    {
      cout << "Prod System: " << *system << endl; delete system;
    }
    string* compression = foo->getCompression();
    if (compression != NULL)
    {
      cout << "Compression: " << *compression << endl; delete compression;
    }
    string* version = foo->getStandardVersion();
    if (version != NULL)
    {
      cout << "Version: " << *version << endl; delete version;
    }
    string* tmeta = foo->getMetaDataDate();
    if (tmeta != NULL)
    {
      cout << "Meta Date: " << *tmeta << endl; delete tmeta;
    }
    cout << "Data Size: " << foo->getDataSize() << endl;
    cout << "Byte Count: " << foo->getByteCount() << endl;
    cout << argv[filecount] << " DOQ Parse Finished" << endl;
    cout << endl;
    delete foo;
  }
  return 0;
}
