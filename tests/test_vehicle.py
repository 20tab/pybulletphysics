import unittest
from bulletphysics import *

class VehicleTest(unittest.TestCase):

    def setUp(self):
        self.tuning = VehicleTuning()

    def test_wheel(self):
        print WheelInfo()

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
