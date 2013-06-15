/** @file Matrix4.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 9/11/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Matrix4 class.
 *
**/

#ifndef APROMATRIX4_H
#define APROMATRIX4_H

#include "Platform.h"
#include "Maths.h"
#include "Vector3.h"

namespace APro
{
    template <typename T>
    class Matrix4
    {
        public:
            //!Constructeur
            /*!
                Construit une matrice 4 par 4 avec un tableau de T.
                \param v : T* tableau de 16 T
            */
            Matrix4(T* v);

            //!Deuxieme constructeur
            /*!Construit la matrice avec 16 T distincts.
            \param v0 : T correspond a valeurs[0]
            \param v1,v2,v3,...,v15
            */
            Matrix4(T v0 = 0, T v1 = 0, T v2 = 0, T v3 = 0,
                          T v4 = 0, T v5 = 0, T v6 = 0, T v7 = 0,
                          T v8 = 0, T v9 = 0, T v10 = 0, T v11 = 0,
                          T v12 = 0, T v13 = 0, T v14 = 0, T v15 = 0);

            //!Initialise la matrice avec un tableau de T donnee
            /*!
                Si tableau est nulle, alors la matrice sera initialisee avec
                la valeur 0.

                \param tableau : T* tableau de 16 T
            */
            void init(const T* tableau = 0);

            //!Cree une matrice egale a celle d'identite.
            void loadIdentity();

            //!Effectue une translation sur la matrice
            /*!
                Translate la matrice mais ne reinitialise pas sa translation.
                \param x : T
                \param y : T
                \param z : T
            */
            void translate(T x, T y, T z);

            //!Effectue une homothetie de la matrice
            /*!
                \param x : T
                \param y : T
                \param z : T
            */
            void scale(T x, T y, T z);

            //!Effectue une rotation de la matrice par rapport a un axe.
            /*!
                \param angle : float
                \param x : T
                \param y : T
                \param z : T
            */
            void rotate(float angle, T x, T y, T z);

            //!Renvoie une reference sur le nombre a la case donnee.
            /*!
                \param _case : unsigned int
                \return float&
            */
            float& operator[](unsigned int _case);

            //!Renvoie le nombre a la case donnee.
            /*!
                \param _case : unsigned int
                \return float
            */
            float operator[](unsigned int _case) const;

            float& operator() (unsigned int row, unsigned int column)
            {
                return byRow[row][column];
            }

            float operator() (unsigned int row, unsigned int column) const
            {
                return byRow[row][column];
            }

            //!Renvoie un tableau de T
            /*!
                \return T* : le tableau
            */
            const T* toT() const { return &(valeurs[0]); }

            //!Renvoie un tableau fait pour OpenGL
            /*!
                \return T* : le tableau
             */
             void toGLMatrix(T* tableau) const
             {
                 tableau[0] = valeurs[0];  tableau[1] = valeurs[4];  tableau[2] = valeurs[8];   tableau[3] = valeurs[12];
                 tableau[4] = valeurs[1];  tableau[5] = valeurs[5];  tableau[6] = valeurs[9];   tableau[7] = valeurs[13];
                 tableau[8] = valeurs[2];  tableau[9] = valeurs[6];  tableau[10] = valeurs[10]; tableau[11] = valeurs[14],
                 tableau[12] = valeurs[3]; tableau[13] = valeurs[7]; tableau[14] = valeurs[11]; tableau[15] = valeurs[15];
             }

             T determinant() const
             {
                 return (byRow[0][0] * byRow[1][1] - byRow[1][0] * byRow[0][1]) * (byRow[2][2] * byRow[3][3] - byRow[3][2] * byRow[2][3])
                    -   (byRow[0][0] * byRow[2][1] - byRow[2][0] * byRow[0][1]) * (byRow[1][2] * byRow[3][3] - byRow[3][2] * byRow[1][3])
                    +   (byRow[0][0] * byRow[3][1] - byRow[3][0] * byRow[0][1]) * (byRow[1][2] * byRow[2][3] - byRow[2][2] * byRow[1][3])
                    +   (byRow[1][0] * byRow[2][1] - byRow[2][0] * byRow[1][1]) * (byRow[0][2] * byRow[3][3] - byRow[3][2] * byRow[0][3])
                    -   (byRow[1][0] * byRow[3][1] - byRow[3][0] * byRow[1][1]) * (byRow[0][2] * byRow[2][3] - byRow[2][2] * byRow[0][3])
                    +   (byRow[2][0] * byRow[3][1] - byRow[3][0] * byRow[2][1]) * (byRow[0][2] * byRow[1][3] - byRow[1][2] * byRow[0][3]);
             }

             Matrix4<T> inverse() const
             {
                T d = determinant();
                if(d == 0) return;

                d = 1.0 / d;
                Matrix4<T> result;
                const Matrix4<T>& m = *this;

                result(0,0) = d * (m(1,1) * (m(2,2) * m(3,3) - m(3,2) * m(2,3)) + m(2,1) * (m(3,2) * m(1,3) - m(1,2) * m(3,3)) + m(3,1) * (m(1,2) * m(2,3) - m(2,2) * m(1,3)));
                result(1,0) = d * (m(1,2) * (m(2,0) * m(3,3) - m(3,0) * m(2,3)) + m(2,2) * (m(3,0) * m(1,3) - m(1,0) * m(3,3)) + m(3,2) * (m(1,0) * m(2,3) - m(2,0) * m(1,3)));
                result(2,0) = d * (m(1,3) * (m(2,0) * m(3,1) - m(3,0) * m(2,1)) + m(2,3) * (m(3,0) * m(1,1) - m(1,0) * m(3,1)) + m(3,3) * (m(1,0) * m(2,1) - m(2,0) * m(1,1)));
                result(3,0) = d * (m(1,0) * (m(3,1) * m(2,2) - m(2,1) * m(3,2)) + m(2,0) * (m(1,1) * m(3,2) - m(3,1) * m(1,2)) + m(3,0) * (m(2,1) * m(1,2) - m(1,1) * m(2,2)));
                result(0,1) = d * (m(2,1) * (m(0,2) * m(3,3) - m(3,2) * m(0,3)) + m(3,1) * (m(2,2) * m(0,3) - m(0,2) * m(2,3)) + m(0,1) * (m(3,2) * m(2,3) - m(2,2) * m(3,3)));
                result(1,1) = d * (m(2,2) * (m(0,0) * m(3,3) - m(3,0) * m(0,3)) + m(3,2) * (m(2,0) * m(0,3) - m(0,0) * m(2,3)) + m(0,2) * (m(3,0) * m(2,3) - m(2,0) * m(3,3)));
                result(2,1) = d * (m(2,3) * (m(0,0) * m(3,1) - m(3,0) * m(0,1)) + m(3,3) * (m(2,0) * m(0,1) - m(0,0) * m(2,1)) + m(0,3) * (m(3,0) * m(2,1) - m(2,0) * m(3,1)));
                result(3,1) = d * (m(2,0) * (m(3,1) * m(0,2) - m(0,1) * m(3,2)) + m(3,0) * (m(0,1) * m(2,2) - m(2,1) * m(0,2)) + m(0,0) * (m(2,1) * m(3,2) - m(3,1) * m(2,2)));
                result(0,2) = d * (m(3,1) * (m(0,2) * m(1,3) - m(1,2) * m(0,3)) + m(0,1) * (m(1,2) * m(3,3) - m(3,2) * m(1,3)) + m(1,1) * (m(3,2) * m(0,3) - m(0,2) * m(3,3)));
                result(1,2) = d * (m(3,2) * (m(0,0) * m(1,3) - m(1,0) * m(0,3)) + m(0,2) * (m(1,0) * m(3,3) - m(3,0) * m(1,3)) + m(1,2) * (m(3,0) * m(0,3) - m(0,0) * m(3,3)));
                result(2,2) = d * (m(3,3) * (m(0,0) * m(1,1) - m(1,0) * m(0,1)) + m(0,3) * (m(1,0) * m(3,1) - m(3,0) * m(1,1)) + m(1,3) * (m(3,0) * m(0,1) - m(0,0) * m(3,1)));
                result(3,2) = d * (m(3,0) * (m(1,1) * m(0,2) - m(0,1) * m(1,2)) + m(0,0) * (m(3,1) * m(1,2) - m(1,1) * m(3,2)) + m(1,0) * (m(0,1) * m(3,2) - m(3,1) * m(0,2)));
                result(0,3) = d * (m(0,1) * (m(2,2) * m(1,3) - m(1,2) * m(2,3)) + m(1,1) * (m(0,2) * m(2,3) - m(2,2) * m(0,3)) + m(2,1) * (m(1,2) * m(0,3) - m(0,2) * m(1,3)));
                result(1,3) = d * (m(0,2) * (m(2,0) * m(1,3) - m(1,0) * m(2,3)) + m(1,2) * (m(0,0) * m(2,3) - m(2,0) * m(0,3)) + m(2,2) * (m(1,0) * m(0,3) - m(0,0) * m(1,3)));
                result(2,3) = d * (m(0,3) * (m(2,0) * m(1,1) - m(1,0) * m(2,1)) + m(1,3) * (m(0,0) * m(2,1) - m(2,0) * m(0,1)) + m(2,3) * (m(1,0) * m(0,1) - m(0,0) * m(1,1)));
                result(3,3) = d * (m(0,0) * (m(1,1) * m(2,2) - m(2,1) * m(1,2)) + m(1,0) * (m(2,1) * m(0,2) - m(0,1) * m(2,2)) + m(2,0) * (m(0,1) * m(1,2) - m(1,1) * m(0,2)));

                return result;
             }

            //!Multiplie deux matrices et renvoie le resultat dans une matrice differente.
            /*!
                \param mat : const Matrix4<T>& matrice a multiplier avec
            */
            Matrix4<T> operator*(const Matrix4<T>& mat) const;

            //!Multiplie deux matrices et stocke le resultat dans cette matrice.
            /*!
                \param mat : const Matrix4<T>&
            */
            void operator*=(const Matrix4<T>& mat);

            //!Egalise deux matrices
            /*!
                \param mat : const Matrix4<T>&
            */
            Matrix4<T>& operator=(const Matrix4<T>& mat);

            //!Test d'egalite sur deux matrices
            /**
             *  \param other : Matrice a tester
             *  \return bool : Resultat
             */
            bool operator==(const Matrix4<T>& other) const {
                return memcmp(valeurs, other.valeurs, sizeof(T) * 16) == 0;
            }

            //!Test de difference sur deux matrices
            /**
             *  \param other : Matrice a tester
             *  \return bool : Resultat
             */
            bool operator!=(const Matrix4<T>& other) const {
                return !(*this == other);
            }

            static Matrix4<T> makeRotationMatrix(double angle, const Vector3<T>& axe)
            {
                Matrix4<T> rotation(NULL);

                angle = toRadian64(angle);

                float longueur = Sqrt(axe[0] * axe[0] + axe[1] * axe[1] + axe[2] * axe[2]);

                if(longueur != 0.0)
                {
                    axe[0] /= longueur;
                    axe[1] /= longueur;
                    axe[2] /= longueur;
                }

                double cosA = Cos(angle);
                double sinA = Sin(angle);
                double ntmp = 1 - cosA;

                rotation[0] = axe[0]*axe[0] * (ntmp) + cosA;
                rotation[1] = axe[0]*axe[1] * (ntmp) - axe[2] * sinA;
                rotation[2] = axe[0]*axe[2] * (ntmp) + axe[1] * sinA;

                rotation[4] = axe[0]*axe[1] * (ntmp) + axe[2] * sinA;
                rotation[5] = axe[1]*axe[1] * (ntmp) + cosA;
                rotation[6] = axe[1]*axe[2] * (ntmp) - axe[0] * sinA;

                rotation[8] = axe[0]*axe[2] * (ntmp) - axe[1] * sinA;
                rotation[9] = axe[1]*axe[2] * (ntmp) + axe[0] * sinA;
                rotation[10] = axe[2]*axe[2] * (ntmp) + cosA;

                rotation[15] = 1.0;

                return rotation;
            }

            static Matrix4<T> getIdentity()
            {
                Matrix4<T> m;
                m.loadIdentity();
                return m;
            }

            static Matrix4<T>& getCachedIdentity()
            {
                IDENTITY.loadIdentity();
                return IDENTITY;
            }

            static Matrix4<T> IDENTITY;

        private:
            union {
                T valeurs[16];///<Valeurs de la matrice
                T byRow[4][4];
            };
    };

    template<typename T>
    Matrix4<T>::Matrix4(const T* v)
    {
        init(v);
    }

    template<typename T>
    Matrix4<T>::Matrix4(T v0, T v1, T v2, T v3,
                          T v4, T v5, T v6, T v7,
                          T v8, T v9, T v10, T v11,
                          T v12, T v13, T v14, T v15)
    {
        valeurs[0] = v0; valeurs[1] = v1; valeurs[2] = v2; valeurs[3] = v3;
        valeurs[4] = v4; valeurs[5] = v5; valeurs[6] = v6; valeurs[7] = v7;
        valeurs[8] = v8; valeurs[9] = v9; valeurs[10] = v10; valeurs[11] = v11;
        valeurs[12] = v12; valeurs[13] = v13; valeurs[14] = v14; valeurs[15] = v15;
    }

    template<typename T>
    Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& mat) const
    {
        static Matrix4<T> resultat;
        resultat.init();

        for(unsigned int k = 0; k < 4; k++)
            for(unsigned int j = 0; j < 4; j++)
                for(unsigned int i = 0; i < 4; i++)
                    resultat[4*j+k] += valeurs[4*j +i] * mat[4*i+k];

        return resultat;
    }

    template<typename T>
    void Matrix4<T>::operator*=(const Matrix4<T>& mat)
    {
        *this = *this * mat;
    }

    template<typename T>
    Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& mat)
    {
        memcpy(valeurs, mat.valeurs, sizeof(T) * 16);
        return *this;
    }

    template<typename T>
    float& Matrix4<T>::operator[](unsigned int _case)
    {
        return valeurs[_case];
    }

    template<typename T>
    float Matrix4<T>::operator[](unsigned int _case) const
    {
        return valeurs[_case];
    }

    template<typename T>
    void Matrix4<T>::rotate(double angle, T x, T y, T z)
    {
        Matrix4<T> rotation(NULL);

        angle = toRadian64(angle);

        T axe[] = {x,y,z};
        float longueur = Sqrt(axe[0] * axe[0] + axe[1] * axe[1] + axe[2] * axe[2]);

        if(longueur != 0.0)
        {
            axe[0] /= longueur;
            axe[1] /= longueur;
            axe[2] /= longueur;
        }

        double cosA = Cos(angle);
        double sinA = Sin(angle);
        double ntmp = 1 - cosA;

        rotation[0] = axe[0]*axe[0] * (ntmp) + cosA;
        rotation[1] = axe[0]*axe[1] * (ntmp) - axe[2] * sinA;
        rotation[2] = axe[0]*axe[2] * (ntmp) + axe[1] * sinA;

        rotation[4] = axe[0]*axe[1] * (ntmp) + axe[2] * sinA;
        rotation[5] = axe[1]*axe[1] * (ntmp) + cosA;
        rotation[6] = axe[1]*axe[2] * (ntmp) - axe[0] * sinA;

        rotation[8] = axe[0]*axe[2] * (ntmp) - axe[1] * sinA;
        rotation[9] = axe[1]*axe[2] * (ntmp) + axe[0] * sinA;
        rotation[10] = axe[2]*axe[2] * (ntmp) + cosA;

        rotation[15] = 1.0;

        *this *= rotation;
    }

    template<typename T>
    void Matrix4<T>::scale(T x,T y,T z)
    {
        Matrix4<T> _scale(NULL);

        _scale[0] = x;
        _scale[5] = y;
        _scale[10] = z;
        _scale[15] = 1;

        *this *= _scale;
    }

    template<typename T>
    void Matrix4<T>::translate(T x,T y,T z)
    {
        valeurs[3] += x;
        valeurs[7] += y;
        valeurs[11] += z;
    }

    template<typename T>
    void Matrix4<T>::init(const T* tableau)
    {
        if(tableau != 0)
            memcpy(valeurs, tableau, sizeof(T) * tableau);
        else
            memset(valeurs, 0, sizeof(T) * tableau);
    }

    template<typename T>
    void Matrix4<T>::loadIdentity()
    {
        init();
        valeurs[0] = 1;
        valeurs[5] = 1;
        valeurs[10] = 1;
        valeurs[15] = 1;
    }

    typedef Matrix4<float> Matrix4F;
    typedef Matrix4<double> Matrix4D;

}

#endif
