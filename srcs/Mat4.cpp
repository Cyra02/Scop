#include "../includes/Mat4.hpp"

Mat4 Mat4::identity()
{
    Mat4 r;
    // esta es la matriz identidad la basica la de los unos en diagobnal y zeros en el resto

    for(int i = 0 ; i < 16;i++)
        r.m[i] = 0.0f;
    r.m[0] = 1.0f;  // m[c * 4 + r]  0 *4 +0 (0,0)
    r.m[5] = 1.0f; // 1 * 4 + 1 (1, 1) tal etc
    r.m[10] = 1.0f;
    r.m[15] = 1.0f;

    return r;

}
// como hemos dicho la ultima coluna es la de la traslacion pues aqui le metemos 
//los valores el ulrimo punto el (3,3) o 15 no porque siempre es 1 para que no se deforme

Mat4 Mat4::translate(float tx, float ty, float tz)
{
    Mat4 r = Mat4::identity();

    r.m[12] = tx;
    r.m[13] = ty;
    r.m[14] = tz;

    return r;
}

Mat4 Mat4::operator*(const Mat4 &o) const
{
    Mat4 r;

    for(int c = 0; c < 4; c ++)
    {
        for(int f = 0; f < 4; f++)
        {
            float sum = 0;
            for(int k =0; k < 4; k++)
                sum += m[k * 4 + f] * o.m[ c * 4 + k];
            r.m[c * 4 + f] = sum;
        }
    }

    return r;

}

Mat4 Mat4::rotateY(float angle)
{
    Mat4 r = Mat4::identity();
    float c = std::cos(angle);
    float s = std::sin(angle);

    r.m[0] =c;
    r.m[8] = s;
    r.m[2] = -s;
    r.m[10] = c;

    return r;
}

Mat4 Mat4::rotateX(float angle)
{
    Mat4 r = Mat4::identity();
    float c = std::cos(angle);
    float s = std::sin(angle);

    r.m[5] =c;
    r.m[6] = s;
    r.m[9] = -s;
    r.m[10] = c;

    return r;
}

Mat4 Mat4::rotateZ(float angle)
{
    Mat4 r = Mat4::identity();
    float c = std::cos(angle);
    float s = std::sin(angle);

    r.m[0] =c;
    r.m[1] = s;
    r.m[4] = -s;
    r.m[5] = c;

    return r;
}
// fov controla el zoom, aspect el ancho alto de la ventana y near y far distancias maxima y minima que se dibujan
//cuadado si cambias el tamaño de la ventana
// Mat4 proj = Mat4::perspectiva(ToRadians(50.0f), 800.0f / 600.0f, 0.1f , 100.0f );
Mat4 Mat4::perspectiva(float fov, float aspect, float near, float far)
{

    Mat4 r;
    for(int i = 0; i < 16; i++)
        r.m[i] = 0.0f;

    float f = 1.0f / std::tan(fov/ 2.0f);

    r.m[0] = f / aspect;
    r.m[5] = f;
    r.m[10] = (far + near) / (near - far);
    r.m[11] = -1.0f;
    r.m[14] = (2.0f * far * near) / (near - far);

    return r;

}

Mat4 Mat4::scale(float sx, float sy, float sz)
{
    Mat4 r = Mat4::identity();

    r.m[0] = sx;
    r.m[5] = sy;
    r.m[10] = sz;
    return r;
}