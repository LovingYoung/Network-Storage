from app import models
from . import app
import os
from flask.ext.login import current_user
class TreeNode:
    def __init__(self, parent=None, sons=None, value=None):
        """
        :type parent: TreeNode
        :type sons: list
        """
        self.parent = parent
        self.sons = sons
        self.value = value

    def addSon(self, newSon):
        """
        :type newSon: TreeNode
        """
        if self.sons is None:
            self.sons = [newSon]
        else:
            self.sons.append(newSon)
        newSon.parent = self

    def setSons(self, newSons):
        """
        :type newSons: list
        """
        self.sons = newSons


def buildTree(files, visit):
    """
    :type files: list
    :type visit: str
    :type file: models.File

    value carry a list of 2-element vector
    the first is the name of file or folder
    the second is MD5 value(file -> MD5, folder -> None)
    """
    if visit is None:
        return []
    if visit[len(visit) - 1] != '/':
        visit = visit + '/'
    visitlen = len(visit.split('/'))
    inthefolder = []
    for file in files:
        try:
            index = file.virtualpath.index(visit)
            if index == 0:
                inthefolder.append(file)
        except ValueError:
            continue
    if len(inthefolder) <= 0:
        return []
    result = []
    for element in inthefolder:
        path = element.virtualpath.split('/')
        if len(path) == visitlen:
            if element.virtualpath != visit:
                if (path[len(path)-1], element.md5) not in result:
                    result.append((path[len(path) - 1], element.md5, os.path.getsize(os.path.join(app.config['UPLOADED_FOLDER'], element.md5[0:2], element.md5))))
            continue
        else:
            if (path[visitlen-1], None, None) not in result:
                result.append((path[visitlen - 1], None, None))
    return result

def getFiles(path):
    files = models.File.query.filter_by(userid=current_user.id).all()
    files = buildTree(files=files, visit=path)
    if files is not None:
        files.sort(key=lambda x: x[0])
    return files;
