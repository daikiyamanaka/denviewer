#include "View.hpp"
#include "Model.hpp"

/*
#include <qgl.h>
#if defined(Q_WS_MAC)
# include <OpenGL/glu.h>
#else
# include <GL/glu.h>
#endif
*/

#include <iostream>

View::View ( Model& model ) : _model ( model )
{
        return;
}

View::~View ( void )
{
        return;
}

void
View::init ( void )
{
        this->_drawMeshList.clear();
        ::glEnable( GL_CULL_FACE );
        ::glEnable ( GL_DEPTH_TEST );
        ::glEnable ( GL_LIGHT0 );
        ::glEnable( GL_LIGHT1 );
        ::glEnable( GL_LIGHT2 );
        ::glShadeModel ( GL_FLAT );
        ::glShadeModel ( GL_SMOOTH );
        const Color3f bg = this->_model.getPreferences().at(0).getBackgroundColor();
        ::glClearColor ( bg.x(), bg.y(), bg.z(), 1 );
        //::glDeleteLists();
        //this->createDisplayList();
        return;
}
void
View::render ( void )
{
        const Color3f bg = this->_model.getPreferences().at(0).getBackgroundColor();
        ::glClearColor(bg.x(), bg.y(), bg.z(), 1);
        ::glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        ::glLoadIdentity();

        //const double zNear = 0.001;
        //const double zFar  = 100000.0;
        double zNear , zFar;
        this->_model.getDisplayRange(zNear , zFar);
        const double fov = this->_model.getCamera().getFieldOfViewAngle();

        // model view.
        const Camera& camera = this->_model.getCamera();
        Eigen::Vector3f eye = camera.getEye();
        Eigen::Vector3f center = camera.getCenter();
        Eigen::Vector3f up = camera.getUpVector();
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();
        int viewport[4];
        ::glGetIntegerv ( GL_VIEWPORT, viewport );
        //::gluPerspective ( fov, viewport[2] * 1.0 / viewport[3],  zNear, zFar );
        double length = this->_model.getCamera().getDistanceToCenter();
        double tanLength = length*std::tan(fov)*2.0;
        ::glOrtho(-tanLength,tanLength,-tanLength,tanLength,zNear,zFar);
        ::gluLookAt ( eye.x(), eye.y(), eye.z(),
                      center.x(), center.y(), center.z(),
                      up.x(), up.y(), up.z() );

        //light
        const Color3f lg = this->_model.getLight(-1).getColor();
        Eigen::Vector3f color;
        color[0] = lg.x();
        color[1] = lg.y();
        color[2] = lg.z();

        Light light1 = this->_model.getLight(0);
        Eigen::Vector3f eye1 = light1.getPosition();
        this->setLight ( light1, GL_LIGHT0, eye1 );
        Light light2 = this->_model.getLight(1);
        Eigen::Vector3f eye2 = light2.getPosition();
        this->setLight ( light2, GL_LIGHT1, eye2 );
        Light light3 = this->_model.getLight(2);
        Eigen::Vector3f eye3 = light3.getPosition();
        this->setLight ( light3, GL_LIGHT2, eye3 );

        this->setLightColor(light1, GL_LIGHT0, color);
        this->setLightColor(light2, GL_LIGHT1, color);
        this->setLightColor(light3, GL_LIGHT2, color);

        //draw mesh

        if(this->_carrow) this->render_arrow();

        //RenderingMode mode = this->_model.getPreference().getRenderingMode() ;
        for( int i = 0 ; i < this->_drawMeshList.size() ; i++){
            if( !this->_model.getMeshCheckState().at(i) ) continue;

            int mode = this->_model.getPreferences().at(i).getRenderingMode();
            GLuint drawlist;
            ShadingMode shading = this->_model.getPreferences().at(i).getShadingMode();
            if( shading == FLAT ) drawlist = this->_drawMeshList[i].first;
            else drawlist = this->_drawMeshList[i].second;

            //std::cerr<< i <<":";

            if ( mode & SURFACE ) {
                //std::cerr<<"Surface";
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonOffset(1.0, 1.0);
                glCallList(drawlist);
                glDisable(GL_POLYGON_OFFSET_FILL);
                glDisable(GL_CULL_FACE);
                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
                ::glEnable ( GL_LIGHTING );
                const Color3f fg = this->_model.getPreferences().at(i).getSurfaceColor();

                //::glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
                GLfloat mat_ambient[4] = {fg.x(), fg.y(), fg.z(), 1.0};
                GLfloat mat_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                GLfloat mat_specular[4] = {0.2, 0.2, 0.2, 1.0};
                GLfloat mat_shininess[1] = {100.0f};

                ::glMaterialfv ( GL_FRONT, GL_AMBIENT,  mat_ambient );
                ::glMaterialfv ( GL_FRONT, GL_DIFFUSE,  mat_diffuse );
                ::glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular );
                ::glMaterialfv ( GL_FRONT, GL_SHININESS,mat_shininess );

                GLfloat mat2_ambient[4] = {1-fg.x(), 1-fg.y(), 1-fg.z(), 1.0};
                GLfloat mat2_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                GLfloat mat2_specular[4] = {0.2, 0.2, 0.2, 1.0};
                GLfloat mat2_shininess[1] = {100.0f};
                ::glMaterialfv ( GL_BACK, GL_AMBIENT,  mat2_ambient );
                ::glMaterialfv ( GL_BACK, GL_DIFFUSE,  mat2_diffuse );
                ::glMaterialfv ( GL_BACK, GL_SPECULAR, mat2_specular );
                ::glMaterialfv ( GL_BACK, GL_SHININESS,mat2_shininess );
                ::glCallList(drawlist);
            }
            if ( mode & WIRE ) {
                //std::cerr<<"Wire";
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                ::glDisable ( GL_LIGHTING );
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
                const Color3f fg = this->_model.getPreferences().at(i).getWireColor();
                ::glColor3f ( fg.x(), fg.y(), fg.z() );
                int width = this->_model.getPreferences().at(i).getWireWidth();
                ::glLineWidth(width);
                ::glCallList(drawlist);
            }
            if( mode & POINTCLOUD ){
                //std::cerr<<"Vertex";
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                ::glDisable ( GL_LIGHTING );
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
                const Color3f fg = this->_model.getPreferences().at(i).getVertexColor();
                ::glColor3f ( fg.x(), fg.y(), fg.z() );
                int radius = this->_model.getPreferences().at(i).getPointSize();///edit after
                int wireWidth = this->_model.getPreferences().at(i).getWireWidth();
                //::glLineWidth(radius);
                ::glPointSize(radius);
                ::glLineWidth(wireWidth);
                //this->render_mesh();
                ::glCallList(drawlist);
            }
            //std::cerr<<std::endl;
        }
        /*
        int mode = this->_model.getPreference().getRenderingMode();
        if ( mode & SURFACE ) {
                   glEnable(GL_POLYGON_OFFSET_FILL);
                   glPolygonOffset(1.0, 1.0);
                   glCallList(this->_drawMesh);
                   glDisable(GL_POLYGON_OFFSET_FILL);
                   glDisable(GL_CULL_FACE);
                   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
                       ::glEnable ( GL_LIGHTING );
                       const Color3f fg = this->_model.getPreference().getSurfaceColor();

                       ::glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
                       GLfloat mat_ambient[4] = {fg.x(), fg.y(), fg.z(), 1.0};
                       GLfloat mat_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                       GLfloat mat_specular[4] = {0.2, 0.2, 0.2, 1.0};
                       GLfloat mat_shininess[1] = {100.0f};

                       ::glMaterialfv ( GL_FRONT, GL_AMBIENT,  mat_ambient );
                       ::glMaterialfv ( GL_FRONT, GL_DIFFUSE,  mat_diffuse );
                       ::glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular );
                       ::glMaterialfv ( GL_FRONT, GL_SHININESS,mat_shininess );

                       GLfloat mat2_ambient[4] = {1-fg.x(), 1-fg.y(), 1-fg.z(), 1.0};
                       GLfloat mat2_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                       GLfloat mat2_specular[4] = {0.2, 0.2, 0.2, 1.0};
                       GLfloat mat2_shininess[1] = {100.0f};
                       ::glMaterialfv ( GL_BACK, GL_AMBIENT,  mat2_ambient );
                       ::glMaterialfv ( GL_BACK, GL_DIFFUSE,  mat2_diffuse );
                       ::glMaterialfv ( GL_BACK, GL_SPECULAR, mat2_specular );
                       ::glMaterialfv ( GL_BACK, GL_SHININESS,mat2_shininess );
                   ::glCallList(this->_drawMesh);

               }
        if ( mode & WIRE ) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
                ::glDisable ( GL_LIGHTING );
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
                const Color3f fg = this->_model.getPreference().getWireColor();
                ::glColor3f ( fg.x(), fg.y(), fg.z() );
                int width = this->_model.getWireWidth();
                ::glLineWidth(width);
                //this->render_mesh();
           ::glCallList(this->_drawMesh);
        } if( mode & POINTCLOUD ){
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            ::glDisable ( GL_LIGHTING );
            ::glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
            const Color3f fg = this->_model.getPreference().getVertexColor();
            ::glColor3f ( fg.x(), fg.y(), fg.z() );
            int radius = this->_model.getPreference().getPointRadius();///edit after
            ::glLineWidth(radius);
            //this->render_mesh();
            ::glCallList(this->_drawMesh);

        }
        //::glCallList(this->_drawMesh);
        //this->render_mesh();
        */



        return;
}
void
View::resize ( const int width, const int height )
{
        ::glViewport ( 0, 0, width, height );
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();

        const double zNear = 0.001;
        const double zFar  = 100000.0;
        const double fov = this->_model.getCamera().getFieldOfViewAngle();
        // Camera
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();
        int viewport[4];
        ::glGetIntegerv ( GL_VIEWPORT, viewport );
        //::gluPerspective ( fov, viewport[2] * 1.0 / viewport[3],  zNear, zFar );
        double length = this->_model.getCamera().getDistanceToCenter();
        double tanLength = length*std::tan(fov)*2.0;
        ::glOrtho(-tanLength,tanLength,-tanLength,tanLength,zNear,zFar);
        ::glMatrixMode ( GL_MODELVIEW );
        return;
}

/*void
View::render_mesh ( void )
{
    const std::vector<Mesh>& meshes = this->_model.getMesh();
    std::vector<bool> checkState= this->_model.getMeshCheckState();
   // std::cout << checkState.size() <<std::endl;

    for(int k=0; k<meshes.size(); k++){

    //for(int k=0; k<checkState.size(); k++){
        if(!checkState[k]){
            continue;
        }
        const Mesh& mesh = meshes[k];
        bool index_data = mesh.IndexDataExists();
        bool vnormal_data = mesh.VNormalDataExists();

        if( index_data ){
            ::glBegin ( GL_TRIANGLES );
            for ( int i = 0 ; i < mesh.getNumFaces() ; i++ ) {

                ShadingMode shading = this->_model.getPreferences().at(i).getShadingMode();
                if(shading == FLAT){
                    const Eigen::Vector3f nrm = mesh.getNormal ( i );
                    ::glNormal3f ( nrm.x(),nrm.y(),nrm.z() );
                }

                    const std::vector<int> index = mesh.getIndex(i);
                    for( int j = 0; j < 3; j++){
                        if(shading == SMOOTH){
                            const Eigen::Vector3f n = mesh.getVNormal( index[j] );
                            ::glNormal3f ( n.x(),n.y(),n.z() );
                        }
                        const Eigen::Vector3f p = mesh.getPosition ( index[j] );
                        ::glVertex3f ( p.x(), p.y(), p.z() );
                    }
            }
            ::glEnd();
        }else{
            ::glBegin ( GL_POINTS );
            for ( int i = 0 ; i < mesh.getNumVertex() ; i++ ) {
                if( vnormal_data ){
                    const Eigen::Vector3f nrm = mesh.getVNormal(i);
                    ::glNormal3f ( nrm.x(),nrm.y(),nrm.z() );
                }
                const Eigen::Vector3f p = mesh.getPosition(i);
                ::glVertex3f ( p.x(), p.y(), p.z() );
            }
             ::glEnd();
        }
        ::glEnd();


    }

    return;
}
*/

void
View::setLight ( const Light& light , const unsigned int number, const Eigen::Vector3f eye)
{

        Color3f amb = light.getAmbient();
        Color3f dif = light.getDiffuse();
        Color3f spe = light.getSpecular();

        //Eigen::Vector3f eye = light.getPosition();
        GLfloat light_ambient[4] = {amb.x(), amb.y(), amb.z(), 1.0f};
        GLfloat light_diffuse[4] = {dif.x(), dif.y(), dif.z(), 1.0f};
        GLfloat light_specular[4] = {spe.x(), spe.y(), spe.z(), 1.0f};
        GLfloat light_position[4] = {eye.x(), eye.y(), eye.z(), 1.0f};
        ::glLightfv ( number, GL_AMBIENT, light_ambient );
        ::glLightfv ( number, GL_DIFFUSE, light_diffuse );
        ::glLightfv ( number, GL_SPECULAR, light_specular );
        ::glLightfv ( number, GL_POSITION, light_position );
        return;
}
void
View::setLightColor( const Light& light , const unsigned int number, const Eigen::Vector3f color){
    GLfloat light_diffuse[4] = {color.x(), color.y(), color.z(), 1.0f};
   //::glLightfv(number, GL_COLOR_INDEX, light_color);
    ::glLightfv(number, GL_DIFFUSE, light_diffuse);
}

void
View::onLight(const unsigned int number){
    ::glEnable(number);
}

void
View::offLight(const unsigned int number){
    ::glDisable(number);
}

/*void
View::createDisplayList( void )
{
    this->_drawMesh = ::glGenLists(1);
    ::glNewList(this->_drawMesh , GL_COMPILE);
    this->render_mesh();
    ::glEndList();
}*/

void
View::render_arrow(void)
{
    glDisable(GL_LIGHTING);

    const CenterArrow& carrow = this->_model.getCenterArrow();

    float scale = carrow.GetScale()/5.0;
    Eigen::Vector3f center = carrow.GetCenter();

    ::glLineWidth(1);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    Eigen::Vector3f up = center + scale*carrow.GetYvec();
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(up[0], up[1], up[2]);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    Eigen::Vector3f side = center - scale*carrow.GetXvec();
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(side[0], side[1], side[2]);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    Eigen::Vector3f in = center + scale*carrow.GetZvec();
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(in[0], in[1], in[2]);
    glEnd();
}

void
View::carrow(bool arrow)
{
    this->_carrow = arrow;
    return;
}

void
View::flatRendering(const Mesh &mesh)
{
    bool index_data = mesh.IndexDataExists();
    bool vcolor_data = mesh.VColorDataExists();

    if( index_data ){
        ::glBegin ( GL_TRIANGLES );
        for ( int i = 0 ; i < mesh.getNumFaces() ; i++ ) {

            const Eigen::Vector3f nrm = mesh.getNormal ( i );
            ::glNormal3f ( nrm.x(),nrm.y(),nrm.z() );
            const std::vector<int> index = mesh.getIndex(i);
            for( int j = 0; j < 3; j++){
                if(vcolor_data){
                    const Eigen::Vector3f c = mesh.getVColor(index[j]);
                    ::glColor3f(c[0],c[1],c[2]);
                }
                const Eigen::Vector3f p = mesh.getPosition ( index[j] );
                ::glVertex3f ( p.x(), p.y(), p.z() );
            }
        }
        ::glEnd();
    }else this->render_NomalVector(mesh);

    return;
}

void
View::smoothRendering(const Mesh &mesh)
{
    bool index_data = mesh.IndexDataExists();
    bool vcolor_data = mesh.VColorDataExists();

    if( index_data ){
        ::glBegin ( GL_TRIANGLES );
        for ( int i = 0 ; i < mesh.getNumFaces() ; i++ ) {

            const std::vector<int> index = mesh.getIndex(i);
            for( int j = 0; j < 3; j++){
                const Eigen::Vector3f n = mesh.getVNormal( index[j] );
                ::glNormal3f ( n.x(),n.y(),n.z() );
                if(vcolor_data){
                    const Eigen::Vector3f c = mesh.getVColor(index[j]);
                    ::glColor3f(c[0],c[1],c[2]);
                }
                const Eigen::Vector3f p = mesh.getPosition ( index[j] );
                ::glVertex3f ( p.x(), p.y(), p.z() );
            }
        }
        ::glEnd();
    }else this->render_NomalVector(mesh);
    return;
}

void
View::render_NomalVector(const Mesh &mesh)
{
    bool vnormal_data = mesh.VNormalDataExists();
    bool vcolor_data = mesh.VColorDataExists();

    float vecLength = this->_model.getVectorLength();
    ::glBegin ( GL_POINTS );
    for ( int i = 0 ; i < mesh.getNumVertex() ; i++ ) {
        if(vcolor_data){
            const Eigen::Vector3f c = mesh.getVColor(i);
            ::glColor3f(c[0],c[1],c[2]);
        }
        const Eigen::Vector3f p = mesh.getPosition(i);
        ::glVertex3f ( p.x(), p.y(), p.z() );
    }
    ::glEnd();
    if( vnormal_data && this->_model.getViewNormal() ){
        for ( int i = 0 ; i < mesh.getNumVertex() ; i++ ) {
            const Eigen::Vector3f p = mesh.getPosition(i);
            const Eigen::Vector3f n = mesh.getVNormal(i);

            if(vcolor_data){
                const Eigen::Vector3f c = mesh.getVColor(i);
                ::glColor3f(c[0],c[1],c[2]);
            }
            ::glBegin ( GL_LINES );
            if( this->_model.getRenderAtCenter() ){
                ::glVertex3f ( p.x()-n.x()*vecLength*0.5f, p.y()-n.y()*vecLength*0.5f, p.z()-n.z()*vecLength*0.5f );
                ::glVertex3f ( p.x()+n.x()*vecLength*0.5f, p.y()+n.y()*vecLength*0.5f, p.z()+n.z()*vecLength*0.5f );
            }else{
                ::glVertex3f ( p.x(), p.y(), p.z() );
                ::glVertex3f ( p.x()+n.x()*vecLength, p.y()+n.y()*vecLength, p.z()+n.z()*vecLength );
            }
            ::glEnd();
        }
    }
    return;
}

RenderPair
View::createRenderPair(const Mesh &mesh)
{
    GLuint flat;
    flat = ::glGenLists(1);
    ::glNewList(flat , GL_COMPILE);
    this->flatRendering(mesh);
    ::glEndList();

    GLuint smooth;
    smooth = ::glGenLists(1);
    ::glNewList(smooth , GL_COMPILE);
    this->smoothRendering(mesh);
    ::glEndList();
    RenderPair pair = std::make_pair<GLuint,GLuint>(flat,smooth);
    return pair;
}

bool
View::addDrawMeshList(int k)
{
    if( k >= this->_model.getMesh().size() ) return false;
    const Mesh& mesh = this->_model.getMesh().at(k);
    this->_drawMeshList.push_back( this->createRenderPair( mesh ) );
    return true;
}

bool
View::updateDrawMeshList(int k)
{
    if( k >= this->_model.getMesh().size() ) return false;

    GLuint list1 =  this->_drawMeshList[k].first;
    GLuint list2 =  this->_drawMeshList[k].second;
    ::glDeleteLists(list1,1);
    ::glDeleteLists(list2,1);

    const Mesh& mesh = this->_model.getMesh().at(k);
    this->_drawMeshList.at(k) = this->createRenderPair(mesh);
    return true;
}

bool
View::deleteDrawMeshList(int k)
{
    if( k >= this->_model.getMesh().size() ) return false;
    this->_drawMeshList.erase( this->_drawMeshList.begin() + k);
    return true;
}


void
View::deleteAllDrawMeshList( void )
{
    for(int k = 0; k < this->_drawMeshList.size(); k++)
    {
        GLuint list1 =  this->_drawMeshList[k].first;
        GLuint list2 =  this->_drawMeshList[k].second;
        ::glDeleteLists(list1,1);
        ::glDeleteLists(list2,1);
    }
    this->_drawMeshList.clear();

    return;
}
