import bpy

def isLogicObject(object):
    return object.type == 'EMPTY'

def isCheckpoint(object):
    if not isLogicObject(object):
        return False
    return object.empty_draw_type == 'CIRCLE'    

def isBoundingBox(object):
    if not isLogicObject(object):
        return False
    return object.empty_draw_type == 'CUBE' 

def write_imakart_map(context, filepath, use_some_setting):
    print("Export Imakart map objects...")
    f = open(filepath, 'w', encoding='utf-8')
    
    #On récupère les objets logiques de la map
    logic_objects = list(filter(isLogicObject, bpy.data.objects))
    
    #On les trie : checkpoints et bouding boxes !
    checkpoints = list(filter(isCheckpoint, logic_objects))
    bounding_boxes = list(filter(isBoundingBox, logic_objects))
    
    #On écrit les checkpoints...
    for checkpoint in checkpoints:
        f.write("Checkpoint %s\n" % checkpoint.name)
        f.write("Location %s %s %s\n" % (checkpoint.location.x, checkpoint.location.y, checkpoint.location.z))
        f.write("Size %s\n" % checkpoint.empty_draw_size)
        
    #Puis les Bounding boxes !
    for bbox in bounding_boxes:
        f.write("BoundingBox %s\n" % bbox.name)
        f.write("Location %s %s %s\n" % (bbox.location.x, bbox.location.y, bbox.location.z))
        f.write("Size %s %s %s\n" % (bbox.scale.x, bbox.scale.y, bbox.scale.z))
        
    f.close()
    
    print("Export finished")

    return {'FINISHED'}

# ExpprintortHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty, IntProperty
from bpy.types import Operator


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
    use_setting = BoolProperty(
            name="Example Boolean",
            description="Example Tooltip",
            default=False,
            )

    type = EnumProperty(
            name="Example Enum",
            description="Choose between two items",
            items=(('OPT_A', "First Option", "Description one"),
                   ('OPT_B', "Second Option", "Description two")),
            default='OPT_A',
            )
    test = IntProperty(
            name="Ma prop",
            description="Blabla",
            default=42,
            )    

    def execute(self, context):
        return write_imakart_map(context, self.filepath, self.use_setting)


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

    # test call
    bpy.ops.export_imakart.game_logic('INVOKE_DEFAULT')