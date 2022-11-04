import unittest
from unittest.mock import MagicMock, patch
import Framework


class Frameworktest(unittest.TestCase):

    def test_local_host_ping(self):
        self.assertTrue(Framework.ping_local_host())

    def test_check_memory(self):
        Framework.run_os_command = MagicMock().return_value("1,3,2")
        self.assertTrue(Framework.check_memory_layout_elf_file("mock"))


if __name__ == '__main__':
    unittest.main()
