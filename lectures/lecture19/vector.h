#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct vector vector ;
struct vector
{ int len; float * val; };

vector new_vector(const int len, const float val);
vector copy_vector(const vector vec);
void print_vector_full( const vector * vec , char* varname );
void delete_vector(vector * vec);
float f_sqrt(float);

#endif