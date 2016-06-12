// $Id: DOQParser.h,v 1.1.1.1 2002-02-19 19:08:25 bmaddox Exp $
// Brian Maddox - USGS MCMC
// Email: bmaddox@usgs.gov
// This class defines the standalone DOQ Parser.  It only provides handlers
// to read the new format (since approx 12/96) DOQ headers.  


#ifndef _DOQPARSER_H_
#define _DOQPARSER_H_

#include <fstream.h>
#include <string.h>
#include <string>


// Definition of class.
class DOQParser
{
    
  ifstream* Stream;      // is called inout in source
  string*   _fileName;
  char*     headerFile;

  char     buffer[80];
  char*    ret;
  char*    position; // position if found in buffer
  string   _temp; 

  bool goodDOQ;  // Used to flag if a read error occurred

  // Identification Section
  string* quadName;
  string* quadrant;
  // neatlines
  int       westHour;
  int       westMinute;
  float     westSecond;
  int       eastHour;
  int       eastMinute;
  float     eastSecond;
  int       northHour;
  int       northMinute;
  float     northSecond;
  int       southHour;
  int       southMinute;
  float     southSecond;
  string*   prodDate;
  
  // Display Section
  string*    rasterOrder; 
  string*    bandOrganization;
  string*    bandContent[3];

  int        bitsPerPixel; 
  long int   samples;
  long int   lines;

  // Registration Section
  string*   horizontalDatum;
  string*   horizCoordSystem; // 0 = UTM, 1 = state plane, 2 = geographic
  int       coordinateZone;
  string*   horizontalUnits;
  float     horizontalResolution;
  string*   secHorizDatum;
  double    xOrigin;
  double    yOrigin;
  double    secxOrigin;
  double    secyOrigin;

  // Other Information
  string*       nation[5];
  string*       states[5];  // Up to 4 state entries in the DOQ header
  double        NWQuadCornerX;
  double        NWQuadCornerY;
  double        NEQuadCornerX;
  double        NEQuadCornerY;
  double        SEQuadCornerX;
  double        SEQuadCornerY;
  double        SWQuadCornerX;
  double        SWQuadCornerY;
  // Secondary corner point coordinates
  double        SNWQuadCornerX;
  double        SNWQuadCornerY;
  double        SNEQuadCornerX;
  double        SNEQuadCornerY;
  double        SSEQuadCornerX;
  double        SSEQuadCornerY;
  double        SSWQuadCornerX;
  double        SSWQuadCornerY;
  
  float         rmseXY; // Root Mean Square error
  string*       imageSource;
  string*       sourceImageID[5];
  string*       sourceImageDate[5];
  string*       sourceDEMDate;
  string*       agency;
  string*       producer;
  string*       productionSystem;
  string*       compression;
  string*       standardVersion;
  string*       metaDataDate;
  long int      dataSize;
  long int      byteCount;


  void  uppercase(void); // convert the buffer to lowercase

  // Methods to set data.  Note:  These functions are called after the 
  // whichToken method is called.  Once it returns the token, the parser
  // will call these functions and they will take the buffer and parse out
  // what they need accordingly 
  // Identification section
  bool setQuadName(void);
  bool setQuadrant(void);
  bool setWestLongitude(void);
  bool setEastLongitude(void);
  bool setNorthLatitude(void);
  bool setSouthLatitude(void);
  bool setProdDate(void);

  // Display Section
  bool setRasterOrder(void);
  bool setBandOrganization(void);
  bool setBandContent(void);
  bool setBitsPerPixel(void);
  bool setSamplesLines(void);

  // Registration Section
  bool setHorizontalDatum(void);
  bool setHorizontalCoordinateSystem(void);
  bool setCoordinateZone(void);
  bool setHorizontalUnits(void);
  bool setHorizontalResolution(void);
  bool setSecondaryHorizontalDatum(void);
  bool setOrigins(void); // sets both X and Y
  bool setSecondaryOrigins(void); // sets both X and Y

  // Other Information
  bool setNation(void);
  bool setStates(void); // Can be called up to 4 times
  bool setNWQuadCorners(void); // as usual
  bool setNEQuadCorners(void);
  bool setSEQuadCorners(void);
  bool setSWQuadCorners(void);
  // Secondary Corner Point Coordinates
  bool setSecondaryNWQuadCorner(void);
  bool setSecondaryNEQuadCorner(void);
  bool setSecondarySEQuadCorner(void);
  bool setSecondarySWQuadCorner(void);

  bool setRMSE(void);
  bool setImageSource(void);
  bool setSourceImageID(void);
  bool setSourceImageDate(void);
  bool setSourceDEMDate(void);
  bool setAgency(void);
  bool setProducer(void);
  bool setProductionSystem(void);
  bool setCompression(void);
  bool setStandardVersion(void);
  bool setMetaDataDate(void);
  bool setDataSize(void);
  bool setByteCount(void);

  void setBad(); // sets the DOQ flag

public:

  DOQParser(const char* fn);
  virtual ~DOQParser();

  bool good();  // returns the flag state

  //  Methods to get at the header data
  // Note:  These return memory which must be destroyed by the caller
  // Identification Section
  string* getQuadName(void);
  string* getQuadrant(void);
  int     getWestHour(void);
  int     getWestMinute(void);
  float   getWestSecond(void);
  int     getEastHour(void);
  int     getEastMinute(void);
  float   getEastSecond(void);
  int     getNorthHour(void);
  int     getNorthMinute(void);
  float   getNorthSecond(void);
  int     getSouthHour(void);
  int     getSouthMinute(void);
  float   getSouthSecond(void);
  string* getProdDate(void);

  // Display section
  string*   getRasterOrder(void);
  string*   getBandOrganization(void);
  string*   getBandContent(int inpos);
  int       getBitsPerPixel(void);
  long int  getSamples(void);
  long int  getLines(void);

  // Registration Section
  string* getHorizontalDatum(void);
  string* getHorizontalCoordinateSystem(void);
  int     getCoordinateZone(void);
  string* getHorizontalUnits(void);
  float   getHorizontalResolution(void);
  string* getSecondaryHorizontalDatum(void);
  double  getXOrigin(void);
  double  getYOrigin(void);
  double  getSecondaryXOrigin(void);
  double  getSecondaryYOrigin(void);

  // Other Information
  int     getNumNations(void);
  string* getNation(int nationnumber);
  int     getNumStates(void); // Returns the number of states in storage
  string* getState(int statenumber); // return the selected state
  double  getNWQuadX(void);
  double  getNWQuadY(void);
  double  getNEQuadX(void);
  double  getNEQuadY(void);
  double  getSEQuadX(void);
  double  getSEQuadY(void);
  double  getSWQuadX(void);
  double  getSWQuadY(void);
  // Secondary Corner Point Values
  double  getSecNWQuadX(void);
  double  getSecNWQuadY(void);
  double  getSecNEQuadX(void);
  double  getSecNEQuadY(void);
  double  getSecSEQuadX(void);
  double  getSecSEQuadY(void);
  double  getSecSWQuadX(void);
  double  getSecSWQuadY(void);

  float     getRMSE(void);
  string*   getImageSource(void);
  int       getNumImageSources(void); // returns number for the following 2
  string*   getSourceImageID(int numimage);
  string*   getSourceImageDate(int numimage);
  string*   getSourceDEMDate(void);
  string*   getAgency(void);
  string*   getProducer(void);
  string*   getProductionSystem(void);
  string*   getCompression(void);
  string*   getStandardVersion(void);
  string*   getMetaDataDate(void);
  long int  getDataSize(void);
  long int  getByteCount(void);


  bool readBuffer(void);   // Read buffer from disk
  int  returnToken(void);  // ID tag and return token

protected:
  bool readHeader(void);  // Called readHeaderData in the source
};

#endif
