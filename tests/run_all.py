import unittest

import test_world
import test_vector3
import test_transform

def test_suite():
    suite = unittest.TestSuite()
    suite.addTest(test_world.test_suite())
    suite.addTest(test_vector3.test_suite())
    suite.addTest(test_transform.test_suite())
    return suite

if __name__ == '__main__':
    unittest.main(defaultTest='test_suite')
