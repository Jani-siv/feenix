import unittest
import Framework

class Frameworktest(unittest.TestCase):

    def test_local_host_ping(self):
        self.assertTrue(Framework.ping_local_host())


if __name__ == '__main__':
    unittest.main()
