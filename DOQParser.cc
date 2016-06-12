// DOQParser.cc  $Id: DOQParser.cc,v 1.1.1.1 2002-02-19 19:08:25 bmaddox Exp $

#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <strstream.h>
#include "DOQParser.h"


DOQParser::DOQParser(const char* filename)
{

  // Make sure we init some stuff (mainly due to Linux and its initialization

  for (int _mycount = 0; _mycount <= 2; _mycount++)
    bandContent[_mycount] = NULL;  // just set so we can test if filled later
 
  for (int _mycount = 0; _mycount <= 4; _mycount++)
  {
    nation[_mycount] = NULL;
    states[_mycount] = NULL;
    sourceImageID[_mycount] = NULL;
    sourceImageDate[_mycount] = NULL;
  }
  
  quadName = NULL;
  quadrant = NULL;
  prodDate = NULL;
  rasterOrder = NULL;
  bandOrganization = NULL;
  horizontalDatum = NULL;
  horizCoordSystem = NULL;
  horizontalUnits = NULL;
  secHorizDatum = NULL;
  imageSource = NULL;
  sourceDEMDate = NULL;
  agency = NULL;
  producer = NULL;
  productionSystem = NULL;
  compression = NULL;
  standardVersion = NULL;
  metaDataDate = NULL;
  goodDOQ = false;
  _fileName = NULL;

  Stream = new ifstream(filename, ios::in | ios::nocreate);

  if (!Stream->good())
  {
    cerr << "DOQParser::DOQParser(): cannot open " << filename << endl;
  }
  else // could open the file ok so go on.
  {
    _fileName = new string(filename);

    goodDOQ = true;
    
    if (!readHeader() )
      // Not valid header information so might as well set fail bit
      setBad();
  }
}


DOQParser::~DOQParser()
{
  // added the NULL tests here mainly for Linux as it's one of the few OS's
  // I've seen which blink if you try to delete a NULL pointer (even though
  // the standard says it should be ok

  if (Stream != NULL)
    delete Stream;
  if (_fileName != NULL)
    delete _fileName;
  if (quadName != NULL)
    delete quadName;
  if (quadrant != NULL)
    delete quadrant;
  if (prodDate != NULL)
    delete prodDate;
  if (rasterOrder != NULL)
    delete rasterOrder;
  if (bandOrganization != NULL)
    delete bandOrganization;
  for (int count = 0; count <= 2; count++)
    if (bandContent[count] != NULL)
      delete bandContent[count];
  if (horizontalDatum != NULL)
    delete horizontalDatum;
  if (horizontalUnits != NULL)
    delete horizontalUnits;
  if (secHorizDatum != NULL)
    delete secHorizDatum;
  if (horizCoordSystem != NULL)
    delete horizCoordSystem;
  for (int count = 0; count <= 4; count++)
    if (nation[count] != NULL)
      delete nation[count];
  for (int count = 0; count <= 4; count++)
    if (states[count] != NULL)
      delete states[count];
  if (imageSource != NULL)
    delete imageSource;
  for (int count = 0; count <= 4; count++)
    if (sourceImageID[count] != NULL)
      delete sourceImageID[count];
  for (int count = 0; count <= 4; count++)
    if (sourceImageDate[count] != NULL)
      delete sourceImageDate[count];
  if (sourceDEMDate != NULL)
    delete sourceDEMDate;
  if (agency != NULL)
    delete agency;
  if (producer != NULL)
    delete producer;
  if (productionSystem != NULL)
    delete productionSystem;
  if (compression != NULL)
    delete compression;
  if (standardVersion != NULL)
    delete standardVersion;
  if (metaDataDate != NULL)
    delete metaDataDate;
}


void DOQParser::setBad(void)
{
  goodDOQ = false;
}

bool DOQParser::good(void)
{
  return goodDOQ;
}


bool DOQParser::readBuffer(void)
{
  for (int _myi = 0; _myi <= 79; _myi++)
    buffer[_myi] = '\0'; // Clear the buffer out
  Stream->getline(buffer, 80);
  return true;
}



// Convert the buffer to uppercase chars so we don't have to worry about case
// sensitivity
void DOQParser::uppercase(void)
{
  for (int _mycount = 0; _mycount <= 79; _mycount++)
    buffer[_mycount] = toupper(buffer[_mycount]);
}



// Return the number of source images used
int DOQParser::getNumImageSources(void)
{
  int _tempcount = 0;
  
  while (_tempcount <= 4)
  {
    if (sourceImageID[_tempcount] == NULL)
      return _tempcount;
    _tempcount++;
  }
}



// Scans buffer and returns a numeric value based on what token is in it
// My first attempt at a real parse, play nice :)
int DOQParser::returnToken(void)
{
  // There are better ways to do this, and will worry about that later :)
  if ( (position = strstr(buffer, "BEGIN_USGS_DOQ_HEADER") ) != NULL)
    return 1;
  else if ( (position = strstr(buffer, "QUADRANGLE_NAME") ) != NULL)
    return 2;
  else if ( (position = strstr(buffer, "QUADRANT") ) != NULL)
    return 3;
  else if ( (position = strstr(buffer, "WEST_LONGITUDE") ) != NULL)
    return 4;
  else if ( (position = strstr(buffer, "EAST_LONGITUDE") ) != NULL)
    return 5;
  else if ( (position = strstr(buffer, "NORTH_LATITUDE") ) != NULL)
    return 6;
  else if ( (position = strstr(buffer, "SOUTH_LATITUDE") ) != NULL)
    return 7;
  else if ( (position = strstr(buffer, "PRODUCTION_DATE") ) != NULL)
    return 8;
  else if ( (position = strstr(buffer, "RASTER_ORDER") ) != NULL)
    return 9;
  else if ( (position = strstr(buffer, "BAND_ORGANIZATION") ) != NULL)
    return 10;
  else if ( (position = strstr(buffer, "BAND_CONTENT") ) != NULL)
    return 11;
  else if ( (position = strstr(buffer, "BITS_PER_PIXEL") ) != NULL)
    return 12;
  else if ( (position = strstr(buffer, "SAMPLES_AND_LINES") ) != NULL)
    return 13;
  else if ( (position = strstr(buffer, "SECONDARY_HORIZONTAL_DATUM") ) != NULL)
    return 19; // moved here since below would always pick up first
  else if ( (position = strstr(buffer, "HORIZONTAL_DATUM") ) != NULL)
    return 14;
  else if ( (position = strstr(buffer, "HORIZONTAL_COORDINATE_SYSTEM") ) != NULL)
    return 15;
  else if ( (position = strstr(buffer, "COORDINATE_ZONE") ) != NULL)
    return 16;
  else if ( (position = strstr(buffer, "HORIZONTAL_UNITS") ) != NULL)
    return 17;
  else if ( (position = strstr(buffer, "HORIZONTAL_RESOLUTION") ) != NULL)
    return 18;
  else if ( (position = strstr(buffer, "SECONDARY_XY_ORIGIN") ) != NULL)
    return 21;
  else if ( (position = strstr(buffer, "XY_ORIGIN") ) != NULL)
    return 20;
  else if ( (position = strstr(buffer, "NATION") ) != NULL)
    return 22;
  else if ( (position = strstr(buffer, "STATE") ) != NULL)
    return 23;
  else if ( (position = strstr(buffer, "NW_QUAD_CORNER_XY") ) != NULL)
    return 24;
  else if ( (position = strstr(buffer, "NE_QUAD_CORNER_XY") ) != NULL)
    return 25;
  else if ( (position = strstr(buffer, "SE_QUAD_CORNER_XY") ) != NULL)
    return 26;
  else if ( (position = strstr(buffer, "SW_QUAD_CORNER_XY") ) != NULL)
    return 27;
  else if ( (position = strstr(buffer, "SECONDARY_NW_QUAD_XY") ) != NULL)
    return 28;
  else if ( (position = strstr(buffer, "SECONDARY_NE_QUAD_XY") ) != NULL)
    return 29;
  else if ( (position = strstr(buffer, "SECONDARY_SE_QUAD_XY") ) != NULL)
    return 30;
  else if ( (position = strstr(buffer, "SECONDARY_SW_QUAD_XY") ) != NULL)
    return 31;
  else if ( (position = strstr(buffer, "RMSE_XY") ) != NULL)
    return 32;
  else if ( (position = strstr(buffer, "IMAGE_SOURCE") ) != NULL)
    return 33;
  else if ( (position = strstr(buffer, "SOURCE_IMAGE_ID") ) != NULL)
    return 34;
  else if ( (position = strstr(buffer, "SOURCE_IMAGE_DATE") ) != NULL)
    return 35;
  else if ( (position = strstr(buffer, "SOURCE_DEM_DATE") ) != NULL)
    return 36;
  else if ( (position = strstr(buffer, "AGENCY") ) != NULL)
    return 37;
  else if ( (position = strstr(buffer, "PRODUCER") ) != NULL)
    return 38;
  else if ( (position = strstr(buffer, "PRODUCTION_SYSTEM") ) != NULL)
    return 39;
  else if ( (position = strstr(buffer, "COMPRESSION") ) != NULL)
    return 40;
  else if ( (position = strstr(buffer, "STANDARD_VERSION") ) != NULL)
    return 41;
  else if ( (position = strstr(buffer, "METADATA_DATE") ) != NULL)
    return 42;
  else if ( (position = strstr(buffer, "DATA_FILE_SIZE") ) != NULL)
    return 43;
  else if ( (position = strstr(buffer, "BYTE_COUNT") ) != NULL)
    return 44;
  else if ( (position = strstr(buffer, "END_USGS_HEADER") ) != NULL)
    return 45;
  else
    return 666; // undefined tag
}
  


bool DOQParser::readHeader(void)
{
  int _tempToken;
  readBuffer();
  if (returnToken() != 1)
  {
    cerr << "Error: " << *_fileName << " does not contain keyword start tag" << endl;
    return false;
  }
  
  readBuffer();
  while ( (_tempToken = returnToken() ) != 45)
  {
    switch (_tempToken)
    {
    case 2:
      setQuadName(); break;
    case 3:
      setQuadrant(); break;
    case 4:
      setWestLongitude(); break;
    case 5:
      setEastLongitude(); break;
    case 6:
      setNorthLatitude();  break;
    case 7:
      setSouthLatitude();  break;
    case 8:
      setProdDate(); break;
    case 9:
      setRasterOrder();  break;
    case 10:
      setBandOrganization(); break;
    case 11:
      setBandContent(); break;
    case 12:
      setBitsPerPixel(); break;
    case 13:
      setSamplesLines(); break;
    case 14:
      setHorizontalDatum(); break;
    case 15:
      setHorizontalCoordinateSystem(); break;
    case 16:
      setCoordinateZone(); break;
    case 17:
      setHorizontalUnits(); break;
    case 18:
      setHorizontalResolution(); break;
    case 19:
      setSecondaryHorizontalDatum(); break;
    case 20:
      setOrigins(); break;
    case 21:
      setSecondaryOrigins(); break;
    case 22:
      setNation(); break;
    case 23:
      setStates(); break;
    case 24:
      setNWQuadCorners(); break;
    case 25:
      setNEQuadCorners(); break;
    case 26:
      setSEQuadCorners(); break;
    case 27:
      setSWQuadCorners(); break;
    case 28:
      setSecondaryNWQuadCorner(); break;
    case 29:
      setSecondaryNEQuadCorner(); break;
    case 30:
      setSecondarySEQuadCorner(); break;
    case 31:
      setSecondarySWQuadCorner(); break;
    case 32:
      setRMSE(); break;
    case 33:
      setImageSource(); break;
    case 34:
      setSourceImageID(); break;
    case 35:
      setSourceImageDate(); break;
    case 36:
      setSourceDEMDate(); break;
    case 37:
      setAgency(); break;
    case 38:
      setProducer(); break;
    case 39:
      setProductionSystem(); break;
    case 40:
      setCompression(); break;
    case 41:
      setStandardVersion(); break;
    case 42:
      setMetaDataDate(); break;
    case 43:
      setDataSize(); break;
    case 44:
      setByteCount(); break;
    default:
    {
    }
    }
    readBuffer();
  }

  return true; // got this far so tis ok
}



// This follows the standard which says names like this should be enclosed
// within quotes.
bool DOQParser::setQuadName(void)
{
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // Assume it's a single word
  {
    istrstream is(buffer, 80);
    quadName = new string;
    is >> _temp;
    is >> *quadName;
    return true;
  }
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\""); // Find the closing quote mark
  *_end = '\0'; // set so we can make a string out of the substring
  quadName = new string(position);
  return true;
}



// Read and set the Quadrant member
bool DOQParser::setQuadrant(void)
{
  istrstream is(buffer, 80);
  quadrant = new string;
  is >> _temp;  // Skip past tag
  is >> *quadrant;
  return true;
}



bool DOQParser::setWestLongitude(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> westHour >> westMinute >> westSecond;
  return true;
}



bool DOQParser::setEastLongitude(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> eastHour >> eastMinute >> eastSecond;
  return true;
}



bool DOQParser::setNorthLatitude(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> northHour >> northMinute >> northSecond;
  return true;
}



bool DOQParser::setSouthLatitude(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> southHour >> southMinute >> southSecond;
  return true;
}



bool DOQParser::setProdDate(void)
{
  istrstream is(buffer, 80);
  prodDate = new string;
  is >> _temp;
  for (int _mycount = 0; _mycount <= 2; _mycount++)
  {
    is >> _temp;
    *prodDate = *prodDate + " " + _temp;
  }
  return true;
}



bool DOQParser::setRasterOrder(void)
{
  uppercase();
  istrstream is(buffer, 80);
  rasterOrder = new string;
  is >> _temp;
  is >> *rasterOrder;
  return true;
}



// This also assumes that the header follows the standard and encloses the
// SINGLE FILE tag within quotes.  Otherwise, checks to see if it's one
// of the other entries like BIP, BIL, ect
bool DOQParser::setBandOrganization(void)
{
  string temp;
  char* _end;
  uppercase();
  istrstream is(buffer, 80);

  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // check for other types
  {
    if ( (position = strstr(buffer, "BIP")) != NULL)
    {
      bandOrganization = new string;
      istrstream is(buffer, 80);
      is >> temp;
      is >> *bandOrganization;
      return true;
    }
    else if ( (position = strstr(buffer, "BIL")) != NULL)
    {
      bandOrganization = new string;
      istrstream is(buffer, 80);
      is >> temp;
      is >> *bandOrganization;
      return true;
    }
    else if ( (position = strstr(buffer, "BSQ")) != NULL)
    {
      bandOrganization = new string;
      istrstream is(buffer, 80);
      is >> temp;
      is >> *bandOrganization;
      return true;
    }
    else
    {
      cout << buffer << endl;
      cerr << "WARNING!.  Unable to determine Band Organization!" << endl;
      return false;
    }
  }

  // Not any of the 3 full color types, so scan for the other quote and return
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  bandOrganization = new string(position);

  return true;
}


// Okie, here, have to keep track of whether or not there's already an entry
// in the list.  If so, add it to the next one
bool DOQParser::setBandContent(void)
{
  string _temp;
  istrstream is(buffer, 80);
  uppercase();
  is >> _temp; // grab keyword and ignore
  is >> _temp; // get the actual value of the field
  if (_temp == "BLACK&WHITE")
  {
    bandContent[0] = new string(_temp);
    return true; // don't have to worry about others in bandContent
  }

  else
  {
    if (bandContent[0] == NULL)
    {
      bandContent[0] = new string(_temp);
      return true;
    }
    else if (bandContent[1] == NULL)
    {
      bandContent[1] = new string(_temp);
      return true;
    }
    else if (bandContent[2] == NULL)
    {
      bandContent[2] = new string(_temp);
      return true;
    }
    else // all slots are full, something wierd is going on
      return false;
  }
}


bool DOQParser::setBitsPerPixel(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> bitsPerPixel;
  return true;
}



bool DOQParser::setSamplesLines(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> samples;
  is >> lines;
  return true;
}



bool DOQParser::setHorizontalDatum(void)
{
  uppercase();
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // assume it's a single word entry
  {
    istrstream is(buffer, 80);
    horizontalDatum = new string;
    is >> _temp;
    is >> *horizontalDatum;
    return true;
  }

  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  horizontalDatum = new string(position);
  return true;
}



bool DOQParser::setHorizontalCoordinateSystem(void)
{
  uppercase();
  istrstream is(buffer, 80);
  is >> _temp;
  is >> _temp;
  horizCoordSystem = new string(_temp);
  return true;
}



bool DOQParser::setCoordinateZone(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> coordinateZone;
  return true;
}



bool DOQParser::setHorizontalUnits(void)
{
  uppercase();
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // assume it's a single word entry
  {
    istrstream is(buffer, 80);
    horizontalUnits = new string;
    is >> _temp;
    is >> *horizontalUnits;
    return true;
  }

  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  horizontalUnits = new string(position);
  return true;
}



bool DOQParser::setHorizontalResolution(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> horizontalResolution;
  return true;
}



bool DOQParser::setSecondaryHorizontalDatum(void)
{
  uppercase();
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // assume it's a single word entry
  {
    istrstream is(buffer, 80);
    secHorizDatum = new string;
    is >> _temp;
    is >> *secHorizDatum;
    return true;
  }

  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  secHorizDatum = new string(position);
  return true;
}



bool DOQParser::setOrigins(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> xOrigin >> yOrigin;
  return true;
}



bool DOQParser::setSecondaryOrigins(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  is >> secxOrigin >> secyOrigin;
  return true;
}



// again, keep track of how many are there
bool DOQParser::setNation(void)
{
  istrstream is(buffer, 80);
  int _where;
  bool flag = false;
  is >> _temp;

  // Go find the next empty slot
  for (int _mycount = 0; _mycount < 5; _mycount++)
  {
    if ( (nation[_mycount] == NULL) && !flag)
    {
      _where = _mycount;
      flag = true;
    }
  }

  nation[_where] = new string;
  is >> *nation[_where];
  return true;
}

bool DOQParser::setStates(void)
{
  istrstream is(buffer, 80);
  int _where;
  bool flag = false;
  is >> _temp;
  
  // go find the next empty slot
  for (int _mycount = 0; _mycount < 5; _mycount++)
  {
    if ( (states[_mycount] == NULL) && !flag)
    {
      _where = _mycount;
      flag = true;
    }
  }

  states[_where] = new string;
  is >> *states[_where];
  return true;
}



bool DOQParser::setNWQuadCorners(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> NWQuadCornerX >> NWQuadCornerY;
  return true;
}



bool DOQParser::setNEQuadCorners(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> NEQuadCornerX >> NEQuadCornerY;
  return true;
}



bool DOQParser::setSEQuadCorners(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> SEQuadCornerX >> SEQuadCornerY;
  return true;
}



bool DOQParser::setSWQuadCorners(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> SWQuadCornerX >> SWQuadCornerY;
  return true;
}



bool DOQParser::setSecondaryNWQuadCorner(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> SNWQuadCornerX >> SNWQuadCornerY;
  return true;
}



bool DOQParser::setSecondaryNEQuadCorner(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> SNEQuadCornerX >> SNEQuadCornerY;
  return true;
}



bool DOQParser::setSecondarySEQuadCorner(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> SSEQuadCornerX >> SSEQuadCornerY;
  return true;
}



bool DOQParser::setSecondarySWQuadCorner(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> SSWQuadCornerX >> SSWQuadCornerY;
  return true;
}



bool DOQParser::setRMSE(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> rmseXY;
  return true;
}



bool DOQParser::setImageSource(void)
{
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // No quotes so can't parse this one
  {
    cerr << "WARNING!  Unable to determine Image Source" << endl;
    return false;
  }
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  imageSource = new string(position);
  return true;
}



bool DOQParser::setSourceImageID(void)
{
  int _where;
  bool flag = false;

  for (int _mycount = 0; _mycount < 5; _mycount++)
  {
    if ( (sourceImageID[_mycount] == NULL) && !flag)
    {
      _where = _mycount;
      flag = true;
    }
  }

  if (_where == 5) // already full
    return false;
  
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL) // Can't parse if not enclosed in quotes
  {
    cerr << "WARNING! Unable to determine Source Image ID" << endl;
    return false;
  }
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  sourceImageID[_where] = new string(position);
  return true;
}


bool DOQParser::setSourceImageDate(void)
{
  istrstream is(buffer, 80);
  int _where;
  bool flag = false;

  for (int _mycount = 0; _mycount < 5; _mycount++)
  {
    if ( (sourceImageDate[_mycount] == NULL) && !flag)
    {
      _where = _mycount;
      flag = true;
    }
  }
  
  if (_where == 5)
    return false;

  is >> _temp;

  sourceImageDate[_where] = new string;
  is >> *sourceImageDate[_where];
  is >> _temp;
  *sourceImageDate[_where] = *sourceImageDate[_where] + " " + _temp;
  is >> _temp;
  *sourceImageDate[_where] = *sourceImageDate[_where] + " " + _temp;
  return true;
}



// Not a pretty way of doing this, but, well, it works :)
bool DOQParser::setSourceDEMDate(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  sourceDEMDate = new string;
  is >> *sourceDEMDate;
  is >> _temp;
  *sourceDEMDate = *sourceDEMDate + " " + _temp;
  is >> _temp;
  *sourceDEMDate = *sourceDEMDate + " " + _temp;
  return true;
}



bool DOQParser::setAgency(void)
{
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL)
  {
    cerr << "WARNING! Unable to set Agency" << endl;
    return false;
  }
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  agency = new string(position);
  return true;
}



bool DOQParser::setProducer(void)
{
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL)
  {
    cerr << "WARNING! Unable to set Producer" << endl;
    return false;
  }
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  producer = new string(position);
  return true;
}



bool DOQParser::setProductionSystem(void)
{
  char* _end;
  position = strstr(buffer, "\""); // set pos to first quote
  if (position == NULL)
  {
    cerr << "WARNING! Unable to set Production System" << endl;
    return false;
  }
  position = position + 1; // skip past the first quotation mark
  _end = strstr(position, "\"");
  *_end = '\0'; // set so we can make a string out of the substring
  productionSystem = new string(position);
  return true;
}



bool DOQParser::setCompression(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  compression = new string;
  is >> *compression;
  is >> _temp;
  *compression = *compression + " " + _temp;
  is >> _temp;
  *compression = *compression + " " + _temp;
  return true;
}



bool DOQParser::setStandardVersion(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  standardVersion = new string;
  is >> *standardVersion;
  is >> _temp;
  *standardVersion = *standardVersion + " " + _temp;
  return true;
}



bool DOQParser::setMetaDataDate(void)
{
  istrstream is(buffer, 80);
  is >> _temp;
  metaDataDate = new string;

  is >> *metaDataDate;
  is >> _temp;
  *metaDataDate = *metaDataDate + " " + _temp;
  is >> _temp;
  *metaDataDate = *metaDataDate + " " + _temp;
  return true;
}



bool DOQParser::setDataSize(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> dataSize;
  return true;
}



bool DOQParser::setByteCount(void)
{
  istrstream is(buffer, 80);
  
  is >> _temp;
  is >> byteCount;
  return true;
}


// Get functions.
// NOTE:  These functions sometimes return dynamically allocated memory that
// the caller must delete

string* DOQParser::getQuadName(void)
{
  if (quadName == NULL)
    return NULL;
  string* retstring = new string(*quadName);
  return retstring;
}



string* DOQParser::getQuadrant(void)
{
  if (quadrant == NULL)
    return NULL;
  string* retstring = new string(*quadrant);
  return retstring;
}


int DOQParser::getWestHour(void)
{
  return westHour;
}



int DOQParser::getWestMinute(void)
{
  return westMinute;
}



float DOQParser::getWestSecond(void)
{
  return westSecond;
}



int DOQParser::getEastHour(void)
{
  return eastHour;
}



int DOQParser::getEastMinute(void)
{
  return eastMinute;
}



float DOQParser::getEastSecond(void)
{
  return eastSecond;
}



int DOQParser::getNorthHour(void)
{
  return northHour;
}



int DOQParser::getNorthMinute(void)
{
  return northMinute;
}



float DOQParser::getNorthSecond(void)
{
  return northSecond;
}



int DOQParser::getSouthHour(void)
{
  return southHour;
}



int DOQParser::getSouthMinute(void)
{
  return southMinute;
}



float DOQParser::getSouthSecond(void)
{
  return southSecond;
}



string* DOQParser::getProdDate(void)
{
  if (prodDate == NULL)
    return NULL;
  string* _mytemp;
  _mytemp = new string(*prodDate);
  return _mytemp;
}



string* DOQParser::getRasterOrder(void)
{
  if (rasterOrder == NULL)
    return NULL;
  string* _retstring = new string(*rasterOrder);
  return _retstring;
}



string* DOQParser::getBandOrganization(void)
{
  if (bandOrganization == NULL)
    return NULL;
  string* _retstring = new string(*bandOrganization);
  return _retstring;;
}



string* DOQParser::getBandContent(int inpos)
{
  if (bandContent[inpos] == NULL)
    return NULL;
  string* _retstring = new string(*bandContent[inpos]);
  return _retstring;
}



int DOQParser::getBitsPerPixel(void)
{
  return bitsPerPixel;
}



long int DOQParser::getSamples(void)
{
  return samples;
}



long int DOQParser::getLines(void)
{
  return lines;
}



string* DOQParser::getHorizontalDatum(void)
{
  if (horizontalDatum == NULL)
    return NULL;
  string* _mytemp = new string(*horizontalDatum);
  return _mytemp;
}



string* DOQParser::getHorizontalCoordinateSystem(void)
{
  if (horizCoordSystem == NULL)
    return NULL;
  string* _mytemp = new string(*horizCoordSystem);
  return _mytemp;
}



int DOQParser::getCoordinateZone(void)
{
  return coordinateZone;
}



string* DOQParser::getHorizontalUnits(void)
{
  if (horizontalUnits == NULL)
    return NULL;
  string* _mytemp = new string(*horizontalUnits);
  return _mytemp;
}



float DOQParser::getHorizontalResolution(void)
{
  return horizontalResolution;
}



string* DOQParser::getSecondaryHorizontalDatum(void)
{
  if (secHorizDatum == NULL)
    return NULL;
  string* _mytemp = new string(*secHorizDatum);
  return _mytemp;
}



double DOQParser::getXOrigin(void)
{
  return xOrigin;
}



double DOQParser::getYOrigin(void)
{
  return yOrigin;
}



double DOQParser::getSecondaryXOrigin(void)
{
  return secxOrigin;
}



double DOQParser::getSecondaryYOrigin(void)
{
  return secyOrigin;
}



int DOQParser::getNumNations(void)
{
  int _mycount = 0;
  while (_mycount != 5)
  {
    if (nation[_mycount] == NULL)
      return (_mycount);
    _mycount++;
  }
}



string* DOQParser::getNation(int nationnumber)
{
  if (nation[nationnumber - 1] == NULL)
    return NULL;
  string* _mytemp = new string(*nation[nationnumber - 1]);
  return _mytemp;
}



int DOQParser::getNumStates(void)
{
  int _mycount = 0;
  while (_mycount != 5)
  {
    if (states[_mycount] == NULL)
      return _mycount;
    _mycount++;
  }
}


string* DOQParser::getState(int statenumber)
{
  if (states[statenumber - 1] == NULL)
    return NULL;
  string* _mystate = new string(*states[statenumber - 1]);
  return _mystate;
}



double DOQParser::getNWQuadX(void)
{
  return NWQuadCornerX;
}



double DOQParser::getNWQuadY(void)
{
  return NWQuadCornerY;
}



double DOQParser::getNEQuadX(void)
{
  return NEQuadCornerX;
}



double DOQParser::getNEQuadY(void)
{
  return NEQuadCornerY;
}



double DOQParser::getSEQuadX(void)
{
  return SEQuadCornerX;
}



double DOQParser::getSEQuadY(void)
{
  return SEQuadCornerY;
}


double DOQParser::getSWQuadX(void)
{
  return SWQuadCornerX;
}


double DOQParser::getSWQuadY(void)
{
  return SWQuadCornerY;
}


double DOQParser::getSecNWQuadX(void)
{
  return SNWQuadCornerX;
}


double DOQParser::getSecNWQuadY(void)
{
  return SNWQuadCornerY;
}


double DOQParser::getSecNEQuadX(void)
{
  return SNEQuadCornerX;
}


double DOQParser::getSecNEQuadY(void)
{
  return SNEQuadCornerY;
}


double DOQParser::getSecSEQuadX(void)
{
  return SSEQuadCornerX;
}


double DOQParser::getSecSEQuadY(void)
{
  return SSEQuadCornerY;
}


double DOQParser::getSecSWQuadX(void)
{
  return SSWQuadCornerX;
}


double DOQParser::getSecSWQuadY(void)
{
  return SSWQuadCornerY;
}


float DOQParser::getRMSE(void)
{
  return rmseXY;
}


string* DOQParser::getImageSource(void)
{
  if (imageSource == NULL)
    return NULL;
  string* _mytemp = new string(*imageSource);
  return _mytemp;
}


string* DOQParser::getSourceImageID(int numimage)
{
  if (sourceImageID[numimage - 1] == NULL)
    return NULL;
  if (numimage <= 5)
  {
    string* _mytemp = new string(*sourceImageID[numimage - 1]);
    return _mytemp;
  }
  else return NULL;
}


string* DOQParser::getSourceImageDate(int numimage)
{
  if ( (numimage <= 5) && (sourceImageDate[numimage - 1] != NULL) )
  {
    string* _mytemp = new string(*sourceImageDate[numimage - 1]);
    return _mytemp;
  }
  else return NULL;
}


string* DOQParser::getSourceDEMDate(void)
{
  if (sourceDEMDate == NULL)
    return NULL;
  string* _mytemp = new string(*sourceDEMDate);
  return _mytemp;
}


string* DOQParser::getAgency(void)
{
  if (agency == NULL)
    return NULL;
  string* _mytemp = new string(*agency);
  return _mytemp;
}


string* DOQParser::getProducer(void)
{
  if (producer == NULL)
    return NULL;
  string* _mytemp = new string(*producer);
  return _mytemp;
}


string* DOQParser::getProductionSystem(void)
{
  if (productionSystem == NULL)
    return NULL;
  string* _mytemp = new string(*productionSystem);
  return _mytemp;
}


string* DOQParser::getCompression(void)
{
  if (compression == NULL)
    return NULL;
  string* _mytemp = new string(*compression);
  return _mytemp;
}


string* DOQParser::getStandardVersion(void)
{
  if (standardVersion == NULL)
    return NULL;
  string* _mytemp = new string(*standardVersion);
  return _mytemp;
}


string* DOQParser::getMetaDataDate(void)
{
  if (metaDataDate == NULL)
    return NULL;
  string* _mytemp = new string(*metaDataDate);
  return _mytemp;
}


long int DOQParser::getDataSize(void)
{
  return dataSize;
}


long int DOQParser::getByteCount(void)
{
  return byteCount;
}



