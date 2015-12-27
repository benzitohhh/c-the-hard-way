Map -> Object "proto"
    -> Room "start"
    -> Room "location"

Room -> Object "proto"
     ->* Room "north", "south", "east", "west"
     -> Monster "bad_guy"

Monster -> Object "proto"
        -> int "hit_points"

Object -> char "description";
          fn "init"
          fn "describe"
          fn "destroy"
          fn "move"
          fn "attack"
