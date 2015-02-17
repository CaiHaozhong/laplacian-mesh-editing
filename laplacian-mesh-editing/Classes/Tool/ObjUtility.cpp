#include "ObjUtility.h"
// int ObjUtility::ReturnType::OBJ_FAIL = 1;
// int ObjUtility::ReturnType::MTL_FAIL = 2;
// int ObjUtility::ReturnType::TEXTURE_FAIL = 3;
ObjUtility::ObjUtility()
{

}

ObjUtility::~ObjUtility()
{

	
}


ObjEntity* ObjUtility::createObjEntity(const char* filename , int& ret)
{
	ret = ReturnType::SUCCESS;

	vector<Vertex*> *m_vertexList = new vector<Vertex*>;
	vector<NormalVector*> *m_normalVectorList = new vector<NormalVector*>;
	vector<TextureCoordinate*> *m_textureCoordinateList = new vector<TextureCoordinate*>;
	vector<Face*> *m_faceList = new vector<Face*>;	
	MaterialDataManager* materialDataManager = NULL;		
	
	ifstream Input(filename);
	if(!Input.is_open())
	{
		ret = ReturnType::OBJ_FAIL;
		return NULL;
	}
	char key[80];	
	while(Input >> key)
	{
		if(ISEQUAL(key,"#"))
			Input.ignore(1024,'\n');//ºöÂÔÒ»ÐÐ
		else if(ISEQUAL(key, "mtllib"))
		{
			materialDataManager = new MaterialDataManager;			
			char name[100];
			Input>>name;
			char filePath[100];
			sprintf_s(filePath,"%s",name);
			materialDataManager->loadMaterialData(filePath,ret);			
			if(ret == ReturnType::MTL_FAIL||ret == ReturnType::TEXTURE_FAIL)
				return NULL;

		}
		else if(ISEQUAL(key,"usemtl"))
		{
			char name[100];
			Input>> name;
			int index = m_faceList->size();
			materialDataManager->addIndexName(index,name);
		}
		else if(ISEQUAL(key,"v"))
		{
			GLdouble x,y,z;
			Input >> x >> y >> z;
			Vertex* v = new Vertex(x,y,z);
			m_vertexList->push_back(v);
			
		}
		else if(ISEQUAL(key,"vn"))
		{
			GLdouble x,y,z;
			Input >> x >> y >> z;
			NormalVector* vn = new NormalVector(x,y,z);
			m_normalVectorList->push_back(vn);
		}
		else if(ISEQUAL(key,"vt"))
		{
			GLdouble x,y,z;
			Input >> x >> y >> z;
			TextureCoordinate* vt = new TextureCoordinate(x,y,z);
			m_textureCoordinateList->push_back(vt);
		}
		else if(ISEQUAL(key,"f"))
		{
			char temp[40];
			Face* f = new Face;
			for(int i = 0; i < 4; i++)
			{
				Input.ignore(1);
				char c = Input.peek();
				if(!(Input.peek() >= '0' && Input.peek() <= '9'))
				{
					//f->m_type = TRIANGLE;
					break;
				}
				Input >> temp;
				int vIndex, vtIndex, vnIndex;
				splitBySlash(temp,strlen(temp),vIndex,vtIndex,vnIndex);
				f->v.push_back(vIndex);
				f->vt.push_back(vtIndex);
				f->vn.push_back(vnIndex);
			}
			m_faceList->push_back(f);
		}
	}
	Input.close();
	return createObjEntity(m_vertexList, m_textureCoordinateList, m_normalVectorList, m_faceList, materialDataManager );
}



void ObjUtility::splitBySlash( char* str, int len, int& a, int& b, int& c )
{
	char s[100];
	int ss[3] = {0,-1,0};
	int i = 0;
	int j = 0;
	int k = 0;
	while(1)
	{
		if (str[i] == '\0')
		{
			sscanf_s(s,"%d",&ss[2]);
			break;
		}
		if (str[i] == '/')
		{
			sscanf_s(s,"%d",&ss[j]);
			j++;
			k = 0;
			memset(s, 0, 100);
			if (str[i+1] == '/')
			{
				i = i + 1;
				j++;
			}
		}
		else{
			s[k] = str[i];
			k++;
		}

		i++;
	}

	a = ss[0];
	b = ss[1];
	c = ss[2];
}

ObjEntity* ObjUtility::createObjEntity( vector<Vertex*> *m_vertexList, vector<TextureCoordinate*> *m_textureCoordinateList, vector<NormalVector*> *m_normalVectorList, vector<Face*> *m_faceList, MaterialDataManager* materialDataManager )
{
	ObjEntity* ret = new ObjEntity;
	if(m_vertexList == NULL || m_faceList == NULL)
		return NULL;
	ret->m_vertexList = m_vertexList;
	ret->m_textureCoordinateList = m_textureCoordinateList;
	ret->m_normalVectorList = m_normalVectorList;
	ret->m_faceList = m_faceList;
	ret->materialDataManager = materialDataManager;

	//init size and position
	GLdouble minx, miny, minz;
	GLdouble maxx, maxy, maxz;
	for(int i = 0; i < m_vertexList->size(); i++)
	{
		Vertex* v = m_vertexList->at(i);
		if(i == 0)
		{
			minx = maxx = v->x; 
			miny = maxy = v->y;
			minz = maxz = v->z;
		}
		else
		{
			if(minx > v->x) minx = v->x;				
			if(maxx < v->x) maxx = v->x;
			if(miny > v->y) miny = v->y;
			if(maxy < v->y) maxy = v->y;
			if(minz > v->z) minz = v->z;
			if(maxz < v->z) maxz = v->z;
		}
	}
 	ret->setSize(Size3D(maxx-minx,maxy-miny,maxz-minz));
 	ret->setCenter(Vector3D((maxx+minx)/2,(maxy+miny)/2,(maxz+minz)/2));
	return ret;
}
