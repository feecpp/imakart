bl_info = {
    "name": "Imakart Exporter",
    "category": "Import-Export",
    "author":       "Jean-Noël Chiganne",
    "blender":      (2,6,9),
    "version":      (0,0,2),
    "location":     "File > Import-Export",
    "description":  "Export Imakart map logic",
    "category":     "Import-Export"
}

import bpy

def isLogicObject(object):
    return object.type == 'EMPTY' or object.type == 'LATTICE'

def isPlayerCheckpoint(object):
    if not isLogicObject(object):
        return False
    return object.empty_draw_type == 'CIRCLE'    

def isOpponentCheckpoint(object):
    if not isLogicObject(object):
        return False
    return object.empty_draw_type == 'CONE'    

def isBoundingBox(object):
    if not isLogicObject(object):
        return False
    return object.empty_draw_type == 'CUBE' 

def isItem(object):
    if not isLogicObject(object):
        return False
    return object.empty_draw_type == 'SPHERE' 

def isFrictionArea(object):
    if not isLogicObject(object):
        return False
    return object.type == 'LATTICE' 

#ATTENTION : les starting points sont des MESH, pas des EMPTY
def isKartStartingPoint(object):
    if object.name.find("Mark") == 0:
        return True
    return False

# !!!!!!!!!! BLENDER INVERSE Y et Z et Z et dans l'autre sens !!!!!!!!!!
def write_imakart_map(context, filepath, use_some_setting):
    print("Export Imakart map objects...")
    f = open(filepath, 'w', encoding='utf-8')
    
    #On récupère les objets logiques de la map
    logic_objects = list(filter(isLogicObject, bpy.data.objects))
    kart_starting_points = list(filter(isKartStartingPoint, bpy.data.objects))
    
    #On les trie : checkpoints, bouding boxes, items, surface de friction !
    opponent_checkpoints = list(filter(isOpponentCheckpoint, logic_objects))
    player_checkpoints = list(filter(isPlayerCheckpoint, logic_objects))
    bounding_boxes = list(filter(isBoundingBox, logic_objects))
    items = list(filter(isItem, logic_objects))
    friction_areas = list(filter(isFrictionArea, logic_objects))
    
    #On écrit les Kart starting point
    for starting_point in kart_starting_points:
        f.write("StartingPoint %s\n" % starting_point.name)
        f.write("location %f %f %f\n" % (starting_point.location.x, starting_point.location.z, -starting_point.location.y))
    
    #On écrit les checkpoints...
    for checkpoint in player_checkpoints:
        f.write("PlayerCheckpoint %s\n" % checkpoint.name)
        f.write("location %f %f %f\n" % (checkpoint.location.x, checkpoint.location.z, -checkpoint.location.y))
        f.write("radius %f\n" % checkpoint.empty_draw_size)
        
    for checkpoint in opponent_checkpoints:
        f.write("OpponentCheckpoint %s\n" % checkpoint.name)
        f.write("location %f %f %f\n" % (checkpoint.location.x, checkpoint.location.z, -checkpoint.location.y))
        f.write("radius %f\n" % 5.0)
        
    #Puis les Bounding boxes 
    for bbox in bounding_boxes:
        #Hack : un cube de scale 1 fait deux unités sous Blender...donc on s'adapte
        scalex = 2 * bbox.scale.x
        scaley = 2 * bbox.scale.y
        scalez = 2 * bbox.scale.z
        print(bbox.name)
        print(scalex)
        f.write("BoundingBox %s\n" % bbox.name)
        f.write("location %f %f %f\n" % (bbox.location.x, bbox.location.z, -bbox.location.y))
        f.write("size %f %f %f\n" % (scalex, scalez, scaley))
        
     #Puis les items 
    for item in items:
        f.write("Item %s\n" % item.name)
        f.write("location %f %f %f\n" % (item.location.x, item.location.z, -item.location.y))
        
    #Et enfin les zones de friction
    for area in friction_areas:
        f.write("FrictionArea %s\n" % area.name)
        f.write("location %f %f %f\n" % (area.location.x, area.location.z, -area.location.y))
        f.write("size %f %f %f\n" % (area.scale.x, area.scale.z, area.scale.y))
        
    f.close()
    
    print("Export finished")

    return {'FINISHED'}

# ExpprintortHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty, IntProperty
from bpy.types import Operator
from bpy.types import INFO_MT_file_export


class ExportImakart(Operator, ExportHelper):
    """Export game logic of an Imakart map"""
    bl_idname = "export_imakart.game_logic"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export Imakart game logic"

    # ExportHelper mixin class uses this
    filename_ext = ".txt"

    filter_glob = StringProperty(
            default="*.txt",
            options={'HIDDEN'},
            )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.

    def execute(self, context):
        return write_imakart_map(context, self.filepath, None)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportImakart.bl_idname, text="Imakart Exporter")


def register():
    bpy.utils.register_class(ExportImakart)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportImakart)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()
    class myPanel(bpy.types.Panel):     # panel to display new property
        bl_space_type = "VIEW_3D"       # show up in: 3d-window
        bl_region_type = "UI"           # show up in: properties panel
        bl_label = "My Panel"           # name of the new panel
     
        def draw(self, context):
            # display value of "foo", of the active object
            self.layout.prop(bpy.context.active_object, '["fileName"]')
 
    bpy.utils.register_class(myPanel)   # register panel
    # test call
    #bpy.ops.export_imakart.game_logic('INVOKE_DEFAULT')
    
