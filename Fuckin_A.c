#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define   BUFFER_SIZE   440000
typedef struct
{
    float left_fp32;
    float right_fp32;
} fp_sample_t;


fp_sample_t buffer[BUFFER_SIZE];


uint16_t head = 0; //pointer to head in buffer
uint8_t flip = 0;

void sample_buffer_put(fp_sample_t *data);
void sample_buffer_get(fp_sample_t * data);
void sample_buffer_get_out(fp_sample_t * data);
void sample_buffer_put_z(fp_sample_t *data, uint16_t z);
void sample_buffer_get_z(fp_sample_t *data, uint16_t z);

void mod_reverb_effekt( fp_sample_t *in, fp_sample_t *out, float in_gain, float fb_gain, uint16_t delay);
void mod_echo_effekt( fp_sample_t *in, fp_sample_t *out);

int main() {
  FILE * pFilein, *pFileout;
  float Huff[44101] = { 0 };
  float Knap = 0;

  int i = BUFFER_SIZE;
  while(i--)
  {
      buffer[i].left_fp32 = 0;
      buffer[i].right_fp32 = 0;
  }

  static fp_sample_t buffer1;
  static fp_sample_t buffer2;
 /* uint16_t iter = 0;
  float delay = 2000, decay = -0.45;
  int layS = (delay * 44.1f);
*/
  pFilein = fopen("dirac16_44_stereo.raw", "r");
  pFileout = fopen("Potatoe.raw", "w");


  if(pFilein == NULL) {
    fputs("Error opening input file\n", stderr);
    exit(1);
  }
  while(feof(pFilein) == 0) {
    fread(&Knap, 4, 1, pFilein);
//stuff
    buffer1.left_fp32 = Knap;

    fread(&Knap, 4, 1, pFilein);

    buffer1.right_fp32 = Knap;

  //  mod_reverb_effekt( &buffer1, &buffer2, -0.25, -0.25, 100 );

   // buffer1 = buffer2;

//    mod_echo_effekt(&buffer1, &buffer2);

 //   buffer1 = buffer2;
    float fb_gain = -0.20;
    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 101 );

    buffer1 = buffer2;
    fb_gain += 0.01;
    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 103 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 107 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 109 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 113 );

    buffer1 = buffer2;
    fb_gain += 0.01;


    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 127 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 131 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 137 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 139 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 149 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 151 );

    buffer1 = buffer2;
    fb_gain += 0.01;


    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 157 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 163 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 167 );

    buffer1 = buffer2;
    fb_gain += 0.01;


    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 173 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 179 );

    buffer1 = buffer2;
    fb_gain += 0.01;

    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 181 );

    buffer1 = buffer2;
    fb_gain += 0.01;


    mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, 191 );

    buffer1 = buffer2;
    fb_gain = -0.20;
/*    uint16_t count = 0;
    uint16_t c = 0;
    uint16_t i = 3;
    float fb_gain = -0.30;
    for ( count = 2 ; count <= 20 ;  )
    {
        for (c = 2 ; c <= i - 1 ; c++ )
        {
          if ( i%c == 0 )
            break;
        }
        if ( c == i )
        {
          mod_reverb_effekt( &buffer1, &buffer2, -0.25, fb_gain, i);
          buffer1 = buffer2;

          fb_gain += 0.01;
          count++;
        }
        i++;
      }
*/

    sample_buffer_get_out( &buffer1);

    Knap = (buffer2.left_fp32 + buffer1.left_fp32);

    fwrite(&Knap, 4, 1, pFileout);

    Knap = (buffer2.right_fp32 + buffer1.right_fp32);

    fwrite(&Knap, 4, 1, pFileout);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}


void mod_reverb_effekt( fp_sample_t *in, fp_sample_t *out, float in_gain, float fb_gain, uint16_t delay)
{
  if(1)
  {
/*  const float in_gain = -0.25;
  const float fb_gain = -0.05;
  const uint16_t delay = 5000;
*/
  fp_sample_t fp_sample;
  sample_buffer_get(&fp_sample);

  fp_sample.left_fp32 = ((in->left_fp32 * in_gain) + ((in->left_fp32 + fp_sample.left_fp32) * fb_gain));
  fp_sample.right_fp32 = ((in->right_fp32 * in_gain) + ((in->left_fp32 + fp_sample.right_fp32) * fb_gain));

  //sample_buffer_get_z(&fp_sample, delay);
  //fp_sample_out.left_fp32 = (fp_sample_out.left_fp32 + fp_sample.left_fp32);
  //fp_sample_out.right_fp32 = (fp_sample_out.right_fp32 + fp_sample.right_fp32);
  sample_buffer_put_z(&fp_sample, delay);

  out->left_fp32 = in->left_fp32;
  out->right_fp32 = in->right_fp32;
  }

}

void sample_buffer_get(fp_sample_t *data)
/*****************************************************************************
 *    Input    : The buffer data should be put into and the data to put in.
 *    Output   :
 *    Function : Inserts data into the buffer.
 *******************************************************************************/
{
  data->left_fp32 = buffer[head].left_fp32;
  data->right_fp32 = buffer[head].right_fp32;
}

void sample_buffer_get_out(fp_sample_t *data)
/*****************************************************************************
 *    Input    : The buffer data should be put into and the data to put in.
 *    Output   :
 *    Function : Inserts data into the buffer.
 *******************************************************************************/
{
  data->left_fp32 = buffer[head].left_fp32;
  data->right_fp32 = buffer[head].right_fp32;

  buffer[head].left_fp32 = 0;
  buffer[head].right_fp32 = 0;

  if (head < (BUFFER_SIZE-1))
    head++;
  else
  {
    flip = 1;
    head = 0;
  }
}

void sample_buffer_put(fp_sample_t *data)
/*****************************************************************************
 *    Input    : The buffer data is to be got from.
 *    Output   :
 *    Function : Gets data from buffer.
 *******************************************************************************/
{
    buffer[head].left_fp32 = data->left_fp32;
    buffer[head].right_fp32 = data->right_fp32;
}

void sample_buffer_put_z(fp_sample_t *data, uint16_t z)
/*****************************************************************************
 *    Input    : The buffer data should be put into and the data to put in.
 *    Output   :
 *    Function : Inserts data into the buffer at location offset from header by z.
 *******************************************************************************/
{
  uint16_t index;

  if( z < BUFFER_SIZE )
  {
    index = (head + z + 1) <= (BUFFER_SIZE - 1) ? head + z : (head + z) - BUFFER_SIZE;
    buffer[index].left_fp32 += data->left_fp32;
    buffer[index].right_fp32 += data->right_fp32;
  }
}

void sample_buffer_get_z(fp_sample_t *data, uint16_t z)
/*****************************************************************************
 *    Input    : The buffer data is to be got from.
 *    Output   :
 *    Function : Gets data from buffer at location offset from header by z.
 *******************************************************************************/
{
  uint16_t index;

  if ((head < z) && !flip)
  {
    index = (head + z) <= (BUFFER_SIZE - 1) ? head + z : (head + z) - BUFFER_SIZE;
    data->left_fp32 = buffer[index].left_fp32;
    data->right_fp32 = buffer[index].right_fp32;
  }
}


void mod_echo_effekt( fp_sample_t *in, fp_sample_t *out)
{
  if(1)
  {
  const float gain = .5;
  const uint16_t delay = 11000;

  fp_sample_t fp_sample;

  fp_sample.left_fp32 = (in->left_fp32 * gain);
  fp_sample.right_fp32 = (in->right_fp32 * gain);

  //sample_buffer_get_z(&fp_sample, delay);
  //fp_sample_out.left_fp32 = (fp_sample_out.left_fp32 + fp_sample.left_fp32);
  //fp_sample_out.right_fp32 = (fp_sample_out.right_fp32 + fp_sample.right_fp32);
  sample_buffer_put_z(&fp_sample, delay);

  out->left_fp32 = in->left_fp32;
  out->right_fp32 = in->right_fp32;
  }

}

