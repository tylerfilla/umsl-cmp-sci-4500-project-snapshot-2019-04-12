#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#


class Core:
    """The cozmonaut core."""

    def __init__(self):
        pass

    #
    # C++ ENTRY POINTS
    #

    def op_list_friends(self, fid: str):
        """List friends."""
        print(f'op_list_friends({fid})')
        print('<< NOT IMPLEMENTED >>')

    def op_remove_friends(self, fid: str):
        """Remove friends."""
        print(f'op_remove_friends({fid})')
        print('<< NOT IMPLEMENTED >>')

    def op_start_interactive(self):
        """Start interactive mode."""
        print('op_start_interactive()')
        print('<< NOT IMPLEMENTED >>')
