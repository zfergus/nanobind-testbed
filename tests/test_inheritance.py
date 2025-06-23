import sys
from pathlib import Path
sys.path.append(str(Path(__file__).resolve().parents[1] / "build")) # noqa

from testbed import A, B, C, D

def test_inheritance():
    b = B(1, 2)
    assert b.a == 1
    assert b.b == 2
    assert b.foo() == 2

    d = D(3, 4)
    assert d.a == 3
    assert d.b == 4
    assert d.foo() == 12
    assert d.x == 1
    assert d.bar() == 42

if __name__ == "__main__":
    test_inheritance()
    print("All tests passed.")