#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

import cv2
from PIL import Image


class Core:
    """The cozmonaut core."""

    def __init__(self, params: dict):
        self.params = params
        self.cap = cv2.VideoCapture(0)

    #
    # Entry Points
    #

    def op_list_friends(self):
        """List friends."""

        print(f'op_list_friends("{self.params.get("friend_id", "")}")')
        print('<< NOT IMPLEMENTED >>')

        # Put relevant initializations here
        pass

    def op_remove_friends(self):
        """Remove friends."""

        print(f'op_remove_friends("{self.params.get("friend_id", "")}")')
        print('<< NOT IMPLEMENTED >>')

        # Put relevant initializations here
        pass

    def op_start_interactive(self):
        """Start interactive mode."""

        # Put relevant initializations here
        pass

    #
    # Camera Functions
    #

    def get_num_cameras(self) -> int:
        """
        :return int: The number of cameras
        """
        return 1

    def read_camera(self, cam: int) -> Image:
        """
        Read a frame from the given camera.

        :return PIL.Image.Image: The camera frame
        """

        # Read a video frame
        ret, frame = self.cap.read()

        # Convert BGR to RGB
        cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Return frame as a PIL image
        return Image.fromarray(frame)

    #
    # Face Functions
    #

    def load_faces(self, dest: dict):
        """
        Load all known faces and their unique IDs. A face ID must not be
        negative, and it must not be zero.

        This may be called at any point during program execution, but it will
        definitely be called when the program starts.

        :param dict dest: The destination for ID-face pairs
        """
        pass

    def on_face_show(self, cam: int, fid: int, x: int, y: int, w: int, h: int):
        """
        Called when a face first shows up in the visual field.

        Each face is given a unique integer ID when it first shows up in the
        visual field. Face detection (finding faces in a picture) is fast, but
        face recognition (figuring out who people are) is comparatively slow. To
        keep things as fast as possible, this function is called as soon as a
        face is detected (before it is recognized), and the C++ engine will do
        a bipartite match to track faces across the visual field. So, this
        integer ID will not immediately match the face IDs provided by the
        load_faces function, but it can still be relied upon to track faces
        across the visual field. At any time, the C++ engine can issue a
        correction via the on_face_correct function.

        :param int cam: The camera ID
        :param int fid: The face ID as described above
        :param int x: The top-left x-coordinate of the face rectangle
        :param int y: The top-left y-coordinate of the face rectangle
        :param int w: The width of the face rectangle
        :param int h: The height of the face rectangle
        """
        pass

    def on_face_correct(self, cam: int, fid_old: int, fid_new: int, x: int, y: int, w: int, h: int):
        """
        Called when a correction is issued for a face already in the visual
        field.

        This is called for any event that causes the C++ engine to consider
        itself wrong about a visible face. For example, when a face that has
        been detected has finally been recognized, this function will be called
        with the recognized face's actual ID (the one from load_faces above).
        Also, the engine routinely tests its assumptions about its bipartite
        match, and it may discover it has made a mistake (by confusing two
        nearby faces, for instance).

        :param int cam: The camera ID
        :param int fid_old: The old face ID
        :param int fid_new: The new face ID
        :param int x: The top-left x-coordinate of the face rectangle
        :param int y: The top-left y-coordinate of the face rectangle
        :param int w: The width of the face rectangle
        :param int h: The height of the face rectangle
        """
        pass

    def on_face_move(self, cam: int, fid: int, x: int, y: int, w: int, h: int):
        """
        Called when a face moved in the visual field.

        :param int cam: The camera ID
        :param int fid: The unique face ID
        :param int x: The top-left x-coordinate of the face rectangle
        :param int y: The top-left y-coordinate of the face rectangle
        :param int w: The width of the face rectangle
        :param int h: The height of the face rectangle
        """
        pass

    def on_face_hide(self, cam: int, fid: int, x: int, y: int, w: int, h: int):
        """
        Called when a face can no longer be seen in the visual field.

        :param int cam: The camera ID
        :param int fid: The unique face ID
        :param int x: The top-left x-coordinate of the face rectangle
        :param int y: The top-left y-coordinate of the face rectangle
        :param int w: The width of the face rectangle
        :param int h: The height of the face rectangle
        """
        pass
