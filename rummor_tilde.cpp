#include "c74_msp.h"

#include "math.hpp"
#include "VultEngine.h"

using namespace c74::max;

static t_class* this_class = nullptr;

struct t_rummor {
	t_pxobject x_obj;

	double level1;
	double level2;
	double env1_a;
	double env1_h;
	double env1_r;
	double env2_a;
	double env2_h;
	double env2_r;
	double pitch;
	double bend;
	double drive;
	double tone;
	double sel_env1;
	double sel_env2;
	double noise_sel;
	double osc_sel;
	double decimate;
	double gate_input;

   	Trummor_do_type processor;

	t_rummor();
	void init();
	double step();
	void changeRate();

	float sr = 48000.f;

};

t_rummor::t_rummor() {
}

void t_rummor::init() {
	Trummor_do_init(processor);
}

void t_rummor::changeRate() {
}

double t_rummor::step() {

   Trummor_setLevel1(processor, level1);
   Trummor_setLevel2(processor, level2);

   Trummor_setEnv1A(processor, env1_a);
   Trummor_setEnv1H(processor, env1_h);
   Trummor_setEnv1R(processor, env1_r);

   Trummor_setEnv2A(processor, env2_a);
   Trummor_setEnv2H(processor, env2_h);
   Trummor_setEnv2R(processor, env2_r);

   Trummor_setPitch(processor, pitch);
   Trummor_setBend(processor, bend);
   Trummor_setDrive(processor, drive);

   Trummor_setTone(processor, tone);

   Trummor_setOscBlend(processor, 0.f);
   Trummor_setNoiseBlend(processor, 0.f);

   Trummor_setEnv1Scale(processor, sel_env1);
   Trummor_setEnv2Scale(processor, sel_env2);

   Trummor_setDecimate(processor, decimate);

   _tuple___real_real_real_real__ out;
   Trummor_do(processor, gate_input / 10.0f, 0.f / 10.0f,  0.f / 10.0f, out);

   return out.field_0;

}

void* rummor_new(void) {
	t_rummor* self = (t_rummor*) object_alloc(this_class);

	dsp_setup((t_pxobject*)self, 0);
	outlet_new(self, "signal");
	self->x_obj.z_misc = Z_NO_INPLACE;

	self->init();

	return (void *)self;
}


void rummor_perform64(t_rummor* self, t_object* dsp64, double** ins, long numins, double** outs, long numouts, long sampleframes, long flags, void* userparam) {
    double    *out = outs[0];   // first outlet

	for (int i=0; i<sampleframes; ++i){
		*out++ = self->step();
	}

	self->gate_input = 0.f;

}

void rummor_free(t_rummor* self) {
	dsp_free((t_pxobject*)self);
}

void rummor_dsp64(t_rummor* self, t_object* dsp64, short* count, double samplerate, long maxvectorsize, long flags) {
	object_method_direct(void, (t_object*, t_object*, t_perfroutine64, long, void*),
						 dsp64, gensym("dsp_add64"), (t_object*)self, (t_perfroutine64)rummor_perform64, 0, NULL);
}


void rummor_assist(t_rummor* self, void* unused, t_assist_function io, long index, char* string_dest) {
	if (io == ASSIST_INLET) {
		switch (index) {
			case 0: 
				strncpy(string_dest,"(parameters) IN", ASSIST_STRING_MAXSIZE); 
				break;
		}
	}
	else if (io == ASSIST_OUTLET) {
		switch (index) {
			case 0: 
				strncpy(string_dest,"(signal) Out", ASSIST_STRING_MAXSIZE); 
				break;
		}
	}
}

void rummor_level1(t_rummor *x, double f)
{
	x->level1 = f;
	/*object_post(&x->m_obj.z_ob, "param_brightness");
	std::string s = std::to_string(x->param_damping);
	object_post(&x->m_obj.z_ob, s.c_str());*/
}

void rummor_level2(t_rummor *x, double f)
{
	x->level2 = f;
}
void rummor_env1_a(t_rummor *x, double f)
{
	x->env1_a = f;
}
void rummor_env1_h(t_rummor *x, double f)
{
	x->env1_h = f;
}
void rummor_env1_r(t_rummor *x, double f)
{
	x->env1_r = f;
}
void rummor_env2_a(t_rummor *x, double f)
{
	x->env2_a = f;
}
void rummor_env2_h(t_rummor *x, double f)
{
	x->env2_h = f;
}
void rummor_env2_r(t_rummor *x, double f)
{
	x->env2_r = f;
}
void rummor_pitch(t_rummor *x, double f)
{
	x->pitch = f;
}
void rummor_bend(t_rummor *x, double f)
{
	x->bend = f;
}
void rummor_drive(t_rummor *x, double f)
{
	x->drive = f;
}
void rummor_tone(t_rummor *x, double f)
{
	x->tone = f;
}

void rummor_sel_env1(t_rummor *x, double f)
{
	x->sel_env1 = f;
}
void rummor_sel_env2(t_rummor *x, double f)
{
	x->sel_env2 = f;
}


void rummor_gate_input(t_rummor *x, double f)
{
	x->gate_input = f;
}

void rummor_decimate(t_rummor *x, double f)
{
	x->decimate = f;
}


void ext_main(void* r) {
	this_class = class_new("rummor~", (method)rummor_new, (method)rummor_free, sizeof(t_rummor), NULL, A_GIMME, 0);

	class_addmethod(this_class,(method) rummor_dsp64, "dsp64",	A_CANT,		0);
	class_addmethod(this_class,(method) rummor_assist, "assist",	A_CANT,		0);


	class_addmethod(this_class,(method) rummor_level1,"LEVEL1",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_level2,"LEVEL2",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_env1_a,"ENV1_A",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_env1_h,"ENV1_H",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_env1_r,"ENV1_R",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_env2_a,"ENV2_A",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_env2_h,"ENV2_H",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_env2_r,"ENV2_R",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_pitch,"PITCH",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_bend,"BEND",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_drive,"DRIVE",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_tone,"TONE",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_sel_env1,"SEL_ENV1",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_sel_env2,"SEL_ENV2",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_decimate,"DECIMATE",A_DEFFLOAT,0);
	class_addmethod(this_class,(method) rummor_gate_input,"GATE_INPUT",A_DEFFLOAT,0);
	 

	class_dspinit(this_class);
	class_register(CLASS_BOX, this_class);
}