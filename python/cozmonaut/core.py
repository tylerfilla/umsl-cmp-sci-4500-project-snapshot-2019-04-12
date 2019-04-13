#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#


class Core:
    """The cozmonaut core."""

    def __init__(self, params: dict):
        self.params = params

    #
    # Entry Points
    #

    def op_list_friends(self):
        """List friends."""
        print(f'op_list_friends("{self.params.get("friend_id", "")}")')
        print('<< NOT IMPLEMENTED >>')

    def op_remove_friends(self):
        """Remove friends."""
        print(f'op_remove_friends("{self.params.get("friend_id", "")}")')
        print('<< NOT IMPLEMENTED >>')

    def op_start_interactive(self):
        """Start interactive mode."""
        print('op_start_interactive()')
        print('<< NOT IMPLEMENTED >>')
