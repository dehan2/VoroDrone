from dronekit import *
from time import *
class drone_get:
    def __init__(self,str):
        vehicle = connect(str,wait_ready=True) 
        self.vehicle = vehicle
    def getLocation(self):
        lat = self.vehicle._location.global_relative_frame.lat
        sleep(0.05)
        lon = self.vehicle._location.global_relative_frame.lon
        sleep(0.05)
        alt = self.vehicle._location.global_relative_frame.alt
        sleep(0.05)
        location=[lat,lon,alt]
        #self.vehicle.close()
        return location
    def armNtakeoff(self,aTargetAltitude):
        print 'armming..'
        while not self.vehicle.is_armable:
            sleep(1)
        self.vehicle.mode  = VehicleMode("GUIDED")
        sleep(0.5)
        self.vehicle.armed = True
        while not self.vehicle.armed:
            sleep(1)
        sleep(0.5)
        self.vehicle.simple_takeoff(aTargetAltitude)
        sleep(0.05)
        #print 'started takeoff..'
    def simpleGoto(self, nextLat, nextLon, nextAlt):
        nextPoint = LocationGlobalRelative(nextLat,nextLon,nextAlt)
        #print nextPoint
        self.vehicle.simple_goto(nextPoint)
        sleep(0.5)
    def land(self):
        print 'landing..'
        self.vehicle.mode  = VehicleMode("RTL")
        sleep(0.05)