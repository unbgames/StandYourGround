#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>

class Collision {

public:
    // Observação: IsColliding espera ângulos em radianos!
    // Para usar graus, forneça a sua própria implementação de Rotate,
    // ou transforme os ângulos no corpo de IsColliding.
    static inline bool IsColliding(const Rect& a, const  Rect& b, float angleOfA, float angleOfB) {
        // std::cout<<a.GetX()<<" " <<a.GetY()<<" "<<a.GetW()<<" "<<a.GetH()<<std::endl;
        // std::cout<<b.GetX()<<" "<<b.GetY()<<" "<<b.GetW()<<" "<<b.GetH()<<std::endl;
        Vec2 A[] = { Vec2( a.GetX(), a.GetY() + a.GetH() ),
            Vec2( a.GetX() + a.GetW(), a.GetY() + a.GetH() ),
            Vec2( a.GetX() + a.GetW(), a.GetY() ),
            Vec2( a.GetX(), a.GetY() )
        };
        Vec2 B[] = { Vec2( b.GetX(), b.GetY() + b.GetH() ),
            Vec2( b.GetX() + b.GetW(), b.GetY() + b.GetH() ),
            Vec2( b.GetX() + b.GetW(), b.GetY() ),
            Vec2( b.GetX(), b.GetY() )
        };

        for (auto& v : A) {
            v = (v - a.Center()).GetRotated(angleOfA) + a.Center();
        }

        for (auto& v : B) {
            v = (v - b.Center()).GetRotated(angleOfB) + b.Center();
        }

        Vec2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

        for (auto& axis : axes) {
            float P[4];

            for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

            float minA = *std::min_element(P, P + 4);
            float maxA = *std::max_element(P, P + 4);

            for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

            float minB = *std::min_element(P, P + 4);
            float maxB = *std::max_element(P, P + 4);

            if (maxA < minB || minA > maxB)
                return false;
        }

        return true;
    }

private:
    static inline float Mag(const Vec2& p) {
        return std::sqrt(p.GetX() * p.GetX() + p.GetY() * p.GetY());
    }

    static inline Vec2 Norm(const Vec2& p) {
        return p * (1.f / Mag(p));
    }

    static inline float Dot(const Vec2& a, const Vec2& b) {
        return a.GetX() * b.GetX() + a.GetY() * b.GetY();
    }

    static inline Vec2 Rotate(const Vec2& p, float angle) {
        float cs = std::cos(angle), sn = std::sin(angle);
        return Vec2 ( p.GetX() * cs - p.GetY() * sn, p.GetX() * sn + p.GetY() * cs );
    }
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver.
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }
