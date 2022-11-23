#include <iostream>

#include "physmath.h"

using namespace std;

int main(void) {
	cout << "Welcome to PhysMath!" << endl;

	{
		cout << "BEGIN MEMORY ALLOCATION TESTS" << endl;

		{
			pmTensor<float> t(4, 64, 64, 64, 2);
			t.fill(0);
			cout << "pmTensor t0 is of order " << t.getOrder() << " and has size " << t.getSize() << ", while using " << t.getMemory() << " Bytes of memory :-)" << endl;
		}

		pmTensor<float> t(3, 8, 8, 8);
		t.fill(0);
		cout << "pmTensor t1 is of order " << t.getOrder() << " and has size " << t.getSize() << ", while using " << t.getMemory() << " Bytes of memory :-)" << endl;

		pmMatrix<float> m(4, 4);
		m.fill(0);
		cout << "pmMatrix m is of order " << m.getOrder() << " and has size " << m.getSize() << ", while using " << m.getMemory() << " Bytes of memory :-)" << endl;

		pmVector<float> v(3);
		v.fill(0);
		cout << "pmVector v is of order " << v.getOrder() << " and has size " << v.getSize() << ", while using " << v.getMemory() << " Bytes of memory :-)" << endl;

		pmScalar<float> s;
		s.fill(0);
		cout << "pmScalar s is of order " << s.getOrder() << " and has size " << s.getSize() << ", while using " << s.getMemory() << " Bytes of memory :-)" << endl;

		cout << "END MEMORY ALLOCATION TESTS" << endl;
	}

	{
		cout << "BEGIN ALGEBRAIC TESTS" << endl;

		pmVectorf v0(3);
		v0.set(0, 0);
		v0.set(1, 1);
		v0.set(2, 2);
		pmVectorf v1(3);
		v1.set(3, 0);
		v1.set(4, 1);
		v1.set(5, 2);
		pmVectorf v2(3);
		v2.set(1, 0);
		v2.set(1, 1);
		v2.set(1, 2);
		pmScalarf v3;
		v3.set(2);

		pmVectorf r = (v0 + v1 - v2) * v3 / v3;

		v0.add(v1);
		v0.subtract(v2);

		v0.scale(v3);
		v0.divide(v3);

		cout << v0 << " == " << r << endl;
		v0.transpose(), r.transpose();
		cout << v0 << " == " << r << endl;

		pmVectorf v4 = v1;

		pmMatrixf m0(3, 2);
		m0.set(0, 0, 0), m0.set(1, 1, 0), m0.set(2, 2, 0);
		m0.set(3, 0, 1), m0.set(4, 1, 1), m0.set(5, 2, 1);
		pmMatrixf m1(2, 3);
		m1.set(6, 0, 0), m1.set(7, 1, 0);
		m1.set(8, 0, 1), m1.set(9, 1, 1);
		m1.set(10, 0, 2), m1.set(11, 1, 2);
		pmMatrixf mi(2, 2);
		mi.loadIdentity(2);

		pmMatrixf m2 = multiply(multiply(m0, m1), mi);

		cout << m0 << endl << "*" << endl << m1 << endl << "=" << endl << m2 << endl;

		pmMatrixd m3(128, 8);
		m3.fill(0, true);
		pmMatrixd m4(40, 128);
		m4.fill(-400, true);
		pmMatrixd m5 = pmMatrixd::multiply(m3, m4);

		pmVectorf v5(2), v6(2), v7(3);
		v5.fill(0, true), v6.fill(2, true), v7.fill(4, true);
		v7.transpose();

		pmMatrixf m6 = v6 * v7 * v3;

		v1.fill(0, true), v2.fill(0, true);
		float x = inner(v1, v2);
		cout << x << endl;

		cout << normalize(v1) << " -> " << normalize(v1).magnitude() << endl;

		pmVectorf v8(3);
		v8.fill(4, true);
		pmVectorf c = -cross(v1, v8);
		cout << c << endl;

		cout << angle(v1, c) << endl;

		cout << "END ALGEBRAIC TESTS" << endl;
	}

	{
		cout << "BEGIN PHYSICS TESTS" << endl;

		pmPosition3f p0(0, 1, 2);
		pmPosition3f p1(3, 4, 5);

		p0.subtract(p1);

		pmVelocity3f v0(2, 3, 4);

		cout << v0.speed() << endl;

		cout << "END PHYSICS TESTS" << endl;
	}

	cout << "Goodbye!" << endl;

	system("pause");

	return 0;
}