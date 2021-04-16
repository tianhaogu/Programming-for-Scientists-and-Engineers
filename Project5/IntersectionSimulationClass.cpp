#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"

void IntersectionSimulationClass::readParametersFromFile (
     const string &paramFname) {
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail()) {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success) {
      paramF >> randomSeedVal;
      if (paramF.fail() || randomSeedVal < 0) {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success) {
      paramF >> timeToStopSim;
      if (paramF.fail() || timeToStopSim <= 0) {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success) {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() || eastWestGreenTime <= 0 || eastWestYellowTime <= 0) {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success) {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() || northSouthGreenTime <= 0 || 
          northSouthYellowTime <= 0) {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success) {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() || eastArrivalMean <= 0 || eastArrivalStdDev < 0) {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success) {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() || westArrivalMean <= 0 || westArrivalStdDev < 0) {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success) {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() || northArrivalMean <= 0 || northArrivalStdDev < 0) {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success) {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() || southArrivalMean <= 0 || southArrivalStdDev < 0) {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success) {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() ||  percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100) {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success) {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const {
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly) {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(const string &travelDir) {
  cout << "Time: " << currentTime << " Scheduled Event Type: ";
  //when current car comes from the east, generate delta time according to the
  //mean and std of arrival time from the east, then schdule the time of the
  //next east arrival by added the event to the eventList.
  if (travelDir == EAST_DIRECTION) {
    int deltaTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
    int targetTime = currentTime + deltaTime;
    EventClass newEvent(targetTime, EVENT_ARRIVE_EAST);
    eventList.insertValue(newEvent);
    cout << "East-Bound Arrival Time: " << targetTime << endl;
  }
  //when current car comes from the east, do the same thing as above.
  if (travelDir == WEST_DIRECTION) {
    int deltaTime = getPositiveNormal(westArrivalMean, westArrivalStdDev);
    int targetTime = currentTime + deltaTime;
    EventClass newEvent(targetTime, EVENT_ARRIVE_WEST);
    eventList.insertValue(newEvent);
    cout << "West-Bound Arrival Time: " << targetTime << endl;
  }
  //when current car comes from the north, do the same thing as above.
  if (travelDir == NORTH_DIRECTION) {
    int deltaTime = getPositiveNormal(northArrivalMean, northArrivalStdDev);
    int targetTime = currentTime + deltaTime;
    EventClass newEvent(targetTime, EVENT_ARRIVE_NORTH);
    eventList.insertValue(newEvent);
    cout << "North-Bound Arrival Time: " << targetTime << endl;
  }
  //when current car comes from the south, do the same thing as above.
  if (travelDir == SOUTH_DIRECTION) {
    int deltaTime = getPositiveNormal(southArrivalMean, southArrivalStdDev);
    int targetTime = currentTime + deltaTime;
    EventClass newEvent(targetTime, EVENT_ARRIVE_SOUTH);
    eventList.insertValue(newEvent);
    cout << "South-Bound Arrival Time: " << targetTime << endl;
  }
  if (currentTime != 0) {
    cout << endl;
  }
}

//This function schdules the next change of light according to the current
//direction (EW/NS) and color (green/yellow) of the light in the eventList
void IntersectionSimulationClass::scheduleLightChange() {
  int deltaTime;
  cout << "Time: " << currentTime << " Scheduled Event Type: "
       << "Light Change to ";
  //if the current light is green in EW direction, schedule the next change
  //as yellow in EW direction, by adding the correspoinding duration.
  if (currentLight == LIGHT_GREEN_EW) {
    deltaTime = eastWestGreenTime;
    EventClass scheduledEvent(currentTime + deltaTime, EVENT_CHANGE_YELLOW_EW);
    eventList.insertValue(scheduledEvent);
    cout << "EW Yellow Time: ";
  }
  //if the current light is yellow in EW direction, schedule the next change
  //as green in NS direction, by adding the correspoinding duration.
  if (currentLight == LIGHT_YELLOW_EW) {
    deltaTime = eastWestYellowTime;
    EventClass scheduledEvent(currentTime + deltaTime, EVENT_CHANGE_GREEN_NS);
    eventList.insertValue(scheduledEvent);
    cout << "NS Green Time: ";
  }
  //if the current light is green in NS direction, schedule the next change
  //as yellow in NS direction, by adding the correspoinding duration.
  if (currentLight == LIGHT_GREEN_NS) {
    deltaTime = northSouthGreenTime;
    EventClass scheduledEvent(currentTime + deltaTime, EVENT_CHANGE_YELLOW_NS);
    eventList.insertValue(scheduledEvent);
    cout << "NS Yellow Time: ";
  }
  //if the current light is yellow in NS direction, schedule the next change
  //as green in EW direction, by adding the correspoinding duration.
  if (currentLight == LIGHT_YELLOW_NS) {
    deltaTime = northSouthYellowTime;
    EventClass scheduledEvent(currentTime + deltaTime, EVENT_CHANGE_GREEN_EW);
    eventList.insertValue(scheduledEvent);
    cout << "EW Green Time: ";
  }
  cout << (currentTime + deltaTime) << endl;
  if (currentTime != 0) {
    cout << endl;
  }
}

//This function handles real event (at top of the sorted eventList)
bool IntersectionSimulationClass::handleNextEvent() {
  //if there are event(s) in the eventList, get the current event information
  if (eventList.getNumElems() != 0) {
    EventClass thisEvent;
    eventList.getElemAtIndex(0, thisEvent);
    currentTime = thisEvent.getTimeOccurs();
    //check whether time is over
    if (currentTime <= timeToStopSim) {
      cout << thisEvent << endl;
      //if find it's car arrival
      if (thisEvent.getType() == EVENT_ARRIVE_EAST || 
          thisEvent.getType() == EVENT_ARRIVE_WEST || 
          thisEvent.getType() == EVENT_ARRIVE_NORTH || 
          thisEvent.getType() == EVENT_ARRIVE_SOUTH) {
        //call the corresponding helper function
        this-> handleArrival(thisEvent);
      }
      //if find it's light change
      else {
        //call the corresponding helper function
        this-> handleLightChange(thisEvent);
      }
      //remove the current event
      EventClass removedEvent;
      eventList.removeFront(removedEvent);
      return true;
    }
    else {
      //call the corresponding helper function
      this-> handleExceededEvent(thisEvent);
      return false;
    }
  }
  else {
    return false;
  }
}

//handel the real event of car arrival
void IntersectionSimulationClass::handleArrival(EventClass &thisEvent) {
  //if the car comes from east, add it to the east queue
  if (thisEvent.getType() == EVENT_ARRIVE_EAST) {
    CarClass scheduledCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(scheduledCar);
    cout << "Time: " << currentTime << " Car #" << scheduledCar.getId()
         << " arrives east-bound - queue length: " 
         << eastQueue.getNumElems() << endl;
    //schedule the next east arrival car
    this-> scheduleArrival(EAST_DIRECTION);
  }
  //if the car comes from west, add it to the east queue
  if (thisEvent.getType() == EVENT_ARRIVE_WEST) {
    CarClass scheduledCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(scheduledCar);
    cout << "Time: " << currentTime << " Car #" << scheduledCar.getId()
         << " arrives west-bound - queue length: " 
         << westQueue.getNumElems() << endl;
    //schedule the next west arrival car
    this-> scheduleArrival(WEST_DIRECTION);
  }
  //if the car comes from north, add it to the east queue
  if (thisEvent.getType() == EVENT_ARRIVE_NORTH) {
    CarClass scheduledCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(scheduledCar);
    cout << "Time: " << currentTime << " Car #" << scheduledCar.getId()
         << " arrives north-bound - queue length: " 
         << northQueue.getNumElems() << endl;
    //schedule the next north arrival car
    this-> scheduleArrival(NORTH_DIRECTION);
  }
  //if the car comes from south, add it to the east queue
  if (thisEvent.getType() == EVENT_ARRIVE_SOUTH) {
    CarClass scheduledCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(scheduledCar);
    cout << "Time: " << currentTime << " Car #" << scheduledCar.getId()
         << " arrives south-bound - queue length: " 
         << southQueue.getNumElems() << endl;
    //schedule the next south arrival car
    this-> scheduleArrival(SOUTH_DIRECTION);
  }
  //calculate the max length of each queue
  if (eastQueue.getNumElems() > maxEastQueueLength) {
    maxEastQueueLength = eastQueue.getNumElems();
  }
  if (westQueue.getNumElems() > maxWestQueueLength) {
    maxWestQueueLength = westQueue.getNumElems();
  }
  if (northQueue.getNumElems() > maxNorthQueueLength) {
    maxNorthQueueLength = northQueue.getNumElems();
  }
  if (southQueue.getNumElems() > maxSouthQueueLength) {
    maxSouthQueueLength = southQueue.getNumElems();
  }
}

//handel the real event of light change
void IntersectionSimulationClass::handleLightChange(EventClass &thisEvent) {
  CarClass removedCar;
  int probAdvance = 0;
  //if the light is changing to green in EW direction
  if (thisEvent.getType() == EVENT_CHANGE_GREEN_EW) {
    currentLight = LIGHT_GREEN_EW;
    cout << "Advancing cars on north-south yellow" << endl;
    int northCount = 0;
    int southCount = 0;
    bool northAdvance = true;
    bool southAdvance = true;
    //check whether there's car waiting in the north queue
    if (northQueue.getNumElems() == 0) {
      cout << "  No north-bound cars waiting to advance on yellow" << endl;
    }
    //if north queue not empty and not blocked
    while (northQueue.getNumElems() > 0 && northAdvance == true &&
           northCount < northSouthYellowTime) {
      //generate probability of first driver passing through yellow light.
      //If pass, remove from north queue
      probAdvance = getUniform(MIN_PROB, MAX_PROB);
      if (probAdvance <= percentCarsAdvanceOnYellow) {
        northQueue.dequeue(removedCar);
        cout << "  Next north-bound car will advance on yellow" << endl;
        cout << "  Car #" << removedCar.getId() 
             << " advances north-bound" << endl;
        northCount += 1;
      }
      else {
        northAdvance = false;
        cout << "  Next north-bound car will NOT advance on yellow" << endl;
      }
    }
    //if south queue not empty and not blocked, do the same thing as above
    if (southQueue.getNumElems() == 0) {
      cout << "  No south-bound cars waiting to advance on yellow" << endl;
    }
    while (southQueue.getNumElems() > 0 && southAdvance == true &&
           southCount < northSouthYellowTime) {
      probAdvance = getUniform(MIN_PROB, MAX_PROB);
      if (probAdvance <= percentCarsAdvanceOnYellow) {
        southQueue.dequeue(removedCar);
        cout << "  Next south-bound car will advance on yellow" << endl;
        cout << "  Car #" << removedCar.getId() 
             << " advances south-bound" << endl;
        southCount += 1;
      }
      else {
        southAdvance = false;
        cout << "  Next south-bound car will NOT advance on yellow" << endl;
      }
    }
    //calculate cars passing and cars remaining
    cout << "North-bound cars advanced on yellow: " << northCount 
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on yellow: " << southCount 
         << " Remaining queue: " << southQueue.getNumElems() << endl;
    numTotalAdvancedNorth += northCount;
    numTotalAdvancedSouth += southCount;
  }
  //if the light is changing to yellow in EW direction
  if (thisEvent.getType() == EVENT_CHANGE_YELLOW_EW) {
    currentLight = LIGHT_YELLOW_EW;
    cout << "Advancing cars on east-west green" << endl;
    int eastCount = 0;
    int westCount = 0;
    //let prescribed number of cars pass through east queue
    while (eastQueue.getNumElems() > 0 && eastCount < eastWestGreenTime) {
      eastQueue.dequeue(removedCar);
      cout << "  Car #" << removedCar.getId() 
           << " advances east-bound" << endl;
      eastCount += 1;
    }
    //west queue, same as above
    while (westQueue.getNumElems() > 0 && westCount < eastWestGreenTime) {
      westQueue.dequeue(removedCar);
      cout << "  Car #" << removedCar.getId() 
           << " advances west-bound" << endl;
      westCount += 1;
    }
    //calculate cars passing and cars remaining
    cout << "East-bound cars advanced on green: " << eastCount 
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on green: " << westCount 
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    numTotalAdvancedEast += eastCount;
    numTotalAdvancedWest += westCount;
  }
  //if the light is changing to green in NS direction, same as the 1st "if"
  if (thisEvent.getType() == EVENT_CHANGE_GREEN_NS) {
    currentLight = LIGHT_GREEN_NS;
    cout << "Advancing cars on east-west yellow" << endl;
    int eastCount = 0;
    int westCount = 0;
    bool eastAdvance = true;
    bool westAdvance = true;
    if (eastQueue.getNumElems() == 0) {
      cout << "  No east-bound cars waiting to advance on yellow" << endl;
    }
    while (eastQueue.getNumElems() > 0 && eastAdvance == true &&
           eastCount < eastWestYellowTime) {
      probAdvance = getUniform(MIN_PROB, MAX_PROB);
      if (probAdvance <= percentCarsAdvanceOnYellow) {
        eastQueue.dequeue(removedCar);
        cout << "  Next east-bound car will advance on yellow" << endl;
        cout << "  Car #" << removedCar.getId() 
             << " advances east-bound" << endl;
        eastCount += 1;
      }
      else {
        eastAdvance = false;
        cout << "  Next east-bound car will NOT advance on yellow" << endl;
      }
    }
    if (westQueue.getNumElems() == 0) {
      cout << "  No west-bound cars waiting to advance on yellow" << endl;
    }
    while (westQueue.getNumElems() > 0 && westAdvance == true &&
           westCount < eastWestYellowTime) {
      probAdvance = getUniform(MIN_PROB, MAX_PROB);
      if (probAdvance <= percentCarsAdvanceOnYellow) {
        westQueue.dequeue(removedCar);
        cout << "  Next west-bound car will advance on yellow" << endl;
        cout << "  Car #" << removedCar.getId() 
             << " advances west-bound" << endl;
        westCount += 1;
      }
      else {
        westAdvance = false;
        cout << "  Next west-bound car will NOT advance on yellow" << endl;
      }
    }
    cout << "East-bound cars advanced on yellow: " << eastCount 
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on yellow: " << westCount 
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    numTotalAdvancedEast += eastCount;
    numTotalAdvancedWest += westCount;
  }
  //if the light is changing to yellow in NS direction, same as the 2nd "if"
  if (thisEvent.getType() == EVENT_CHANGE_YELLOW_NS) {
    currentLight = LIGHT_YELLOW_NS;
    cout << "Advancing cars on north-south green" << endl;
    int northCount = 0;
    int southCount = 0;
    while (northQueue.getNumElems() > 0 && northCount < northSouthGreenTime) {
      northQueue.dequeue(removedCar);
      cout << "  Car #" << removedCar.getId() 
           << " advances north-bound" << endl;
      northCount += 1;
    }
    while (southQueue.getNumElems() > 0 && southCount < northSouthGreenTime) {
      southQueue.dequeue(removedCar);
      cout << "  Car #" << removedCar.getId() 
           << " advances south-bound" << endl;
      southCount += 1;
    }
    cout << "North-bound cars advanced on green: " << northCount 
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on green: " << southCount 
         << " Remaining queue: " << southQueue.getNumElems() << endl;
    numTotalAdvancedNorth += northCount;
    numTotalAdvancedSouth += southCount;
  }
  //schdule the next light change
  this-> scheduleLightChange();
}

//handle the first event that exceeds the time limit
void IntersectionSimulationClass::handleExceededEvent(EventClass &thisEvent) {
  //print the exceeded event's time and type
  cout << "Next event occurs AFTER the simulation end time (Event Type: ";
  if (thisEvent.getType() == EVENT_ARRIVE_EAST) {
    cout << "East-Bound Arrival ";
  }
  if (thisEvent.getType() == EVENT_ARRIVE_WEST) {
    cout << "West-Bound Arrival ";
  }
  if (thisEvent.getType() == EVENT_ARRIVE_NORTH) {
    cout << "North-Bound Arrival ";
  }
  if (thisEvent.getType() == EVENT_ARRIVE_SOUTH) {
    cout << "South-Bound Arrival ";
  }
  if (thisEvent.getType() == EVENT_CHANGE_GREEN_EW) {
    cout << "Light Change to EW Green ";
  }
  if (thisEvent.getType() == EVENT_CHANGE_YELLOW_EW) {
    cout << "Light Change to EW Yellow ";
  }
  if (thisEvent.getType() == EVENT_CHANGE_GREEN_NS) {
    cout << "Light Change to NS Green ";
  }
  if (thisEvent.getType() == EVENT_CHANGE_YELLOW_NS) {
    cout << "Light Change to NS Yellow ";
  }
  cout << "Time " << thisEvent.getTimeOccurs() << ")!" << endl;
}

void IntersectionSimulationClass::printStatistics() const {
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
