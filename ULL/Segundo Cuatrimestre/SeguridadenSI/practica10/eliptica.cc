#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>

using namespace std;

// Structure to represent a point on the elliptic curve
struct Point {
    int x;
    int y;
    bool isInfinity;

    // Constructor for defect
    Point(int x_coord, int y_coord) : x(x_coord), y(y_coord), isInfinity(false) {}
    
    // Constructor with parameters
    Point() : x(0), y(0), isInfinity(true) {}
    
    // Check if two points are equal
    bool operator==(const Point& other) const {
        if (isInfinity && other.isInfinity) return true;
        if (isInfinity || other.isInfinity) return false;
        return x == other.x && y == other.y;
    }
};

// Function for modular inverse using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1; // In case that does not exist
}

// Function to evaluate the function (x^3 + ax + b) module p
int evaluateCurve(int x, int a, int b, int p) {
    int x_squared = (x * x) % p;
    int x_cubed = (x_squared * x) % p;
    int ax = (a * x) % p;
    return (x_cubed + ax + b) % p;
}

// Function to check if n is a quadratic residue modulo p
// find y / y² = n (mod p)
bool isQuadraticResidue(int n, int p) {
    for (int i = 0; i < p; i++) {
        if ((i * i) % p == n) {
            return true;
        }
    }
    return false;
}

// Function to find every square root of n mod p
vector<int> findSquareRoots(int n, int p) {
    vector<int> roots;
    for (int i = 0; i < p; i++) {
        if ((i * i) % p == n) {
            roots.push_back(i);
        }
    }
    return roots;
}

// Function to add two points on the elliptic curve
Point addPoints(const Point& P, const Point& Q, int a, int p) {
    // Handle point at infinity cases
    if (P.isInfinity) return Q;
    if (Q.isInfinity) return P;
    
    // Check if points are inverses of each other
    if (P.x == Q.x && P.y == (p - Q.y) % p) {
        return Point(); // Return point at infinity
    }
    
    int lambda;
    
    // Check if points are the same
    if (P.x == Q.x && P.y == Q.y) {
        // Formula for doubling a point
        int numerator = (3 * P.x * P.x + a) % p;
        int denominator = (2 * P.y) % p;
        lambda = (numerator * modInverse(denominator, p)) % p;
    } else {
        // Formula for adding different points
        int numerator = (Q.y - P.y + p) % p;
        int denominator = (Q.x - P.x + p) % p;
        lambda = (numerator * modInverse(denominator, p)) % p;
    }
    
    int x3 = (lambda * lambda - P.x - Q.x + 2 * p) % p;
    int y3 = (lambda * (P.x - x3 + p) - P.y + p) % p;
    
    return Point(x3, y3);
}

// Function to multiply a point by a scalar k
Point scalarMultiply(const Point& P, int k, int a, int p) {
    if (k == 0 || P.isInfinity) {
        return Point(); // Return point at infinity
    }
    
    if (k == 1) {
        return P;
    }
    
    if (k % 2 == 1) {
        return addPoints(P, scalarMultiply(P, k - 1, a, p), a, p);
    }
    
    Point Q = scalarMultiply(P, k / 2, a, p);
    return addPoints(Q, Q, a, p);
}

// Function to find all points on the elliptic curve
vector<Point> findAllPoints(int a, int b, int p) {
    vector<Point> points;
    points.push_back(Point()); // Add point at infinity
    
    for (int x = 0; x < p; x++) {
        int rhs = evaluateCurve(x, a, b, p); // side right of the ecuation x³ + ax + b
        if (isQuadraticResidue(rhs, p)) {  // if is a QuadraticResidue save it and find all the posible values of y
            vector<int> y_values = findSquareRoots(rhs, p);
            for (int y : y_values) {
                points.push_back(Point(x, y));
            }
        }
    }
    
    return points;
}

// Function to encode a message as a point on the curve
/**
 * @brief  Function to encode a message as a point on the curve
 * 
 * @param m mensage to codify
 * @param a coeficient a
 * @param b coeficient b
 * @param p module p
 * @param M space size
 * @return Point 
 */
Point encodeMessage(int m, int a, int b, int p, int M) {
    int h = p / M;  // divide range in "M" zones
    if (h * M >= p) 
      h--;
    
    for (int j = 0; j < h; j++) {
        int x = (m * h + j) % p;
        int rhs = evaluateCurve(x, a, b, p);
        
        if (isQuadraticResidue(rhs, p)) {
            vector<int> y_values = findSquareRoots(rhs, p);
            return Point(x, y_values[0]);
        }
    }
    
    // If no valid point is found (should not happen with correctly chosen parameters)
    return Point();
}

int main() {
    // Input parameters
    int p = 11;
    int a = 1;
    int b = 1;
    Point G(3, 8);  // Initial point
    int dA = 3;  // Key secret
    int dB = 2;  // key secret
    int message = 3;
    int M = 4; // Message space size
    
    // Find all points on the curve
    vector<Point> curvePoints = findAllPoints(a, b, p);
    
    // Print all points on the curve
    cout << "Points on the curve: ";
    bool first = true;
    for (const Point& point : curvePoints) {
        if (point.isInfinity) continue; // Skip point at infinity for output
        if (!first) cout << ",";
        cout << "(" << point.x << "," << point.y << ")";
        first = false;
    }
    cout << endl;
    
    // Compute public keys
    Point publicB = scalarMultiply(G, dB, a, p); // Public key
    Point publicA = scalarMultiply(G, dA, a, p);  // Public key
    
    cout << "Clave pública de B: punto dB*G = " << dB << "(" << G.x << "," << G.y << ")=(" 
         << publicB.x << "," << publicB.y << ")" << endl;
    
    cout << "Clave pública de A: punto dA*G = " << dA << "(" << G.x << "," << G.y << ")=(" 
         << publicA.x << "," << publicA.y << ")" << endl;
    
    // Additional scalar multiplications for demonstration
    Point P4 = scalarMultiply(G, 4, a, p);
    Point P5 = scalarMultiply(G, 5, a, p);
    
    cout << "4(" << G.x << "," << G.y << ")=(" << P4.x << "," << P4.y << "). ";
    cout << "5(" << G.x << "," << G.y << ")=(" << P5.x << "," << P5.y << ")" << endl;
    
    // Compute shared secret
    Point secretA = scalarMultiply(publicB, dA, a, p);  // They have the same solution 
    Point secretB = scalarMultiply(publicA, dB, a, p);  // They have the same solution
    
    cout << "Clave secreta compartida calculada por A: " << dA << "*(" << publicB.x << "," 
         << publicB.y << ")=(" << secretA.x << "," << secretA.y << ")" << endl;
    
    cout << "Clave secreta compartida calculada por B: " << dB << "*(" << publicA.x << "," 
         << publicA.y << ")=(" << secretB.x << "," << secretB.y << ")" << endl;
    
    // Encode message in a point of the eliptic curve
    int h = p / M;
    cout << "M=" << M << endl;
    cout << "h=" << h << "<" << p << "/" << M << endl;
    
    Point messagePoint = encodeMessage(message, a, b, p, M);
    cout << "Mensaje original codificado como punto Qm =(" << message << "*" << h 
         << "," << messagePoint.y << ")=(" << messagePoint.x << "," << messagePoint.y << ")" << endl;
    
    // ElGamal encryption
    Point ciphertext1 = addPoints(messagePoint, secretA, a, p);

    // Public key A, Qm and shared secret 
    
    cout << "Mensaje cifrado y clave pública enviados de A a B: {Qm+dA*(dB*G), dA*G} = {(" 
         << messagePoint.x << "," << messagePoint.y << ")+(" << secretA.x << "," << secretA.y 
         << "), (" << publicA.x << "," << publicA.y << ")}={(" << ciphertext1.x << "," 
         << ciphertext1.y << "),(" << publicA.x << "," << publicA.y << ")}" << endl;
    
    return 0;
}