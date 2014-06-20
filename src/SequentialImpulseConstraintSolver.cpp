#include "pybulletphysics.h"

static void
SequentialImpulseConstraintSolver_dealloc(bulletphysics_SequentialImpulseConstraintSolverObject* self)
{
        delete(self->solver);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
SequentialImpulseConstraintSolver_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_SequentialImpulseConstraintSolverObject *self = (bulletphysics_SequentialImpulseConstraintSolverObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->solver = new btSequentialImpulseConstraintSolver();
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_SequentialImpulseConstraintSolverType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.SequentialImpulseConstraintSolver", /*tp_name*/
    sizeof(bulletphysics_SequentialImpulseConstraintSolverObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)SequentialImpulseConstraintSolver_dealloc,    /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "SequentialImpulseConstraintSolver object",           /* tp_doc */
};

void pybulletphysics_add_SequentialImpulseConstraintSolver(PyObject *module) {
	bulletphysics_SequentialImpulseConstraintSolverType.tp_new = SequentialImpulseConstraintSolver_new;

        if (PyType_Ready(&bulletphysics_SequentialImpulseConstraintSolverType) < 0)
                return;	

	Py_INCREF(&bulletphysics_SequentialImpulseConstraintSolverType);

        PyModule_AddObject(module, "SequentialImpulseConstraintSolver", (PyObject *)&bulletphysics_SequentialImpulseConstraintSolverType);
}
