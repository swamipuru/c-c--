#include<stdio.h>
#include<python2.7/Pytho.h>

static PyObject *pycalc_sum(PyObject *self, PyObject *args){
 int a,b;
 if(!PyArgs_ParseTuple(args,"ii",&a,&b))
  return NULL;
 return Py_BuildValue("i",(a+b));
}

static PyObject *pycalc_subtract(PyObject *self, PyObject *args){
 int a,b;
 if(!PyArgs_ParseTuple(args, "ii",(&a,&b))
  reutrn NULL;
 return Py_BuildValue("i",(a-b));
}

static PyObject *pycalc_multiplies(PyObjet *self, PyObject *args){
 int a,b;
 if(!PyArgs_ParseTuple(args, "ii",(&a,&b))
  return NULL;
 return Py_BuildValue("i",(a*b));
}

static PyObject *pycalc_divides(PyObject *slef, PyObject *args){
 int  x,y;
 if(!PyArgs_ParseTuple(args, "ii",&x,&y))
  return NULL;  
 if(y != 0)
  returnPy_BuildValue("i",(x/y));
 else
  print "Math error: Division by zero!";
}

int main(int argc, char *argv[]){
 Py_SetProgramName(argv[0]);
 Py_Initialize();
 initpycalc();
 return 0;
}
