
from obj import *
from buffer import Buffer
from pygame import image
from OpenGL.GL import *
import glm

class Model(object):
    def __init__(self, filename):
        objFile = Obj(filename)

        self.vertices = objFile.vertices
        self.texCoords = objFile.texcoords
        self.normals = objFile.normals
        self.faces = objFile.faces

        self.texture = None

        self.buffer = Buffer( self.BuildBuffer() )

        self.translation = glm.vec3(0,0,0)
        self.rotation = glm.vec3(0,0,0)
        self.scale = glm.vec3(1,1,1)

        self.active_shaders = None

    def GetModelMatrix(self):
        # M = T * R * S
        # R = pitch * yaw * roll

        identity = glm.mat4(1)

        translateMat = glm.translate(identity, self.translation)

        pitchMat = glm.rotate(identity, glm.radians(self.rotation.x), glm.vec3(1,0,0))
        yawMat = glm.rotate(identity, glm.radians(self.rotation.y), glm.vec3(0,1,0))
        rollMat = glm.rotate(identity, glm.radians(self.rotation.z), glm.vec3(0,0,1))

        rotationMat = pitchMat * yawMat * rollMat

        scaleMat = glm.scale(identity, self.scale)

        return translateMat * rotationMat * scaleMat


    def BuildBuffer(self):
        
        data = [ ]
        

        for faces in self.faces:

            faceVerts =[]

            for i in range(len(faces)):
                vert = []

                position = self.vertices[faces[i][0] - 1]

                for value in position:
                    vert.append(value)


                vrt = self.texCoords[faces[i][1] - 1]

                for value in vrt:
                    vert.append(value)

                normals = self.normals[faces[i][2] - 1]

                for value in normals:
                    vert.append(value)

                faceVerts.append(vert)

            for value in faceVerts[0]: data.append(value)
            for value in faceVerts[1]: data.append(value)
            for value in faceVerts[2]: data.append(value)

            if len(faceVerts) == 4:
                for value in faceVerts[0]: data.append(value)
                for value in faceVerts[2]: data.append(value)
                for value in faceVerts[3]: data.append(value)

        return data
    
    def AddTexture(self, textureFilename):

        self.textureSurface = image.load(textureFilename)
        self.textureData = image.tostring(self.textureSurface, "RGB", True)
        self.texture = glGenTextures(1)
        

    def Render(self):
        # Dar la textura

        if self.texture is not None:

            glActiveTexture(GL_TEXTURE0)
            glBindTexture(GL_TEXTURE_2D, self.texture)

            glTexImage2D(GL_TEXTURE_2D,
                        0,
                        GL_RGB,
                        self.textureSurface.get_width(),
                        self.textureSurface.get_height(),
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        self.textureData)
            
            glGenerateMipmap(GL_TEXTURE_2D)

        self.buffer.Render()

    


                



