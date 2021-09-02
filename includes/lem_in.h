/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:30:02 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:42:39 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "colors.h"
# include "X.h"
# include "keys.h"

# define BUFF 4000000
# define START 0
# define END 1
# define ROOM -1
# define WIN_W 1366
# define WIN_H 768
# define SPEED 25
# define MSIZE 120
# define NBLINE 120

# define INTS sizeof(int)
# define INTPS sizeof(int*)
# define CHARS sizeof(char)
# define CHARPS sizeof(char*)
# define BS sizeof(unsigned char)
# define BPS sizeof(unsigned char*)
# define CAPS sizeof(t_cap)
# define CAPPS sizeof(t_cap*)
# define ROOMS sizeof(t_room)
# define QS sizeof(t_queue)
# define ULLI unsigned long long int

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_fpoint
{
	float				x;
	float				y;
}						t_fpoint;

typedef struct			s_ang
{
	int					ptx;
	int					pty;
	int					tmp;
	int					d0;
	int					d1;
	int					dd;
	int					ptxx;
	int					ptyy;
	int					q;
	int					ml1x;
	int					ml1y;
	int					ml1bx;
	int					ml1by;
	int					ml2x;
	int					ml2y;
	int					ml2bx;
	int					ml2by;
	int					clr;
	float				off;
	double				ang;
	double				sang;
	double				cang;
}						t_ang;

typedef struct			s_murphy
{
	int					u;
	int					v;
	int					ku;
	int					kt;
	int					kv;
	int					kd;
	int					ks;
	int					tk;
	int					oct2;
	int					quad4;
	int					last1x;
	int					last1y;
	int					last2x;
	int					last2y;
	int					first1x;
	int					first1y;
	int					first2x;
	int					first2y;
	int					tempx;
	int					tempy;
}						t_murphy;

typedef struct			s_ite
{
	int					atemp1;
	int					atemp2;
	int					ftmp1;
	int					ftmp2;
	int					m1x;
	int					m1y;
	int					m2x;
	int					m2y;
	int					fix;
	int					fiy;
	int					lax;
	int					lay;
	int					curx;
	int					cury;
	int					px[4];
	int					py[4];
}						t_ite;

typedef struct			s_bren
{
	int					x;
	int					y;
	int					dx;
	int					dy;
	int					s1;
	int					s2;
	int					swapdir;
	int					error;
	size_t				count;
	size_t				n;
	int					m;
	int					o;
}						t_bren;

typedef struct			s_img
{
	void				*ptr;
	int					dimx;
	int					dimy;
	int					bpp;
	int					endian;
	int					size_line;
	int					*pixel;
}						t_img;

typedef struct			s_visu
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_img				banner;
	int					win_w;
	int					win_h;
	int					minb;
	int					clr[NBR_CLR];
}						t_visu;

typedef unsigned char	t_bool;

typedef struct			s_queue
{
	int					*q;
	size_t				len;
	int					tosend;
}						t_queue;

typedef struct			s_pipe
{
	int					*p;
	size_t				len;
}						t_pipe;

typedef struct			s_room
{
	char				*name;
	t_pipe				pipes;
	int					inpath;
	int					blocked;
	int					x;
	int					y;
	int					clr;
}						t_room;

typedef struct			s_env
{
	char				**graph;
	char				*raw;
	char				**rgraph;
	char				**toprint;
	t_room				*rooms;
	t_bren				**diff;
	unsigned int		vert;
	int					source;
	int					sink;
	ULLI				index;
	unsigned int		ant;
	unsigned int		antshow;
	unsigned char		end;
	unsigned int		flow;
	t_queue				**paths;
	t_queue				*ants;
	t_bool				succes;
	int					min;
	int					max;
	int					extra;
	int					curr;
	int					deep;
	char				vis;
	int					xmax;
	int					ymax;
	int					flowmax;
	int					outmin;
	int					maxblock;
	int					from;
	int					set;
	int					step;
	int					togo;
	int					iter;
	int					nbroom;
	short				flag;
	short				io;
	t_visu				v;
}						t_env;

void					img_fill_rect_circ(t_env *env, t_point start,
						int rad, int color);
void					img_fill_rect_circ_border(t_env *env, t_point start,
						int rad, int color);
void					img_reset(t_env *env);
void					img_pixel_put(t_env *env, t_point a, int clr);
int						check_exist(t_env *env);
void					bren_helperone(t_bren *b, int x1, int x2, int y1);
void					bren_helpertwo(t_bren *b);
void					init_ite(t_ite *ite, t_murphy *m, t_ang *ang);
void					continue_ite(t_ite *ite, t_murphy *m, t_ang *ang);
void					iterate_ite(t_ite *ite, t_ang *ang);
void					set_ite_p(t_ite *ite, t_ang *ang);
void					set_murphy(t_murphy *m, t_ang *ang);
void					ite_loop(t_env *env, t_bren *b, t_ite *ite, t_ang *ang);
t_bool					beufeuseu(t_env *env, int *parent);
int						saumon_fume(t_env *env);
t_queue					dijkstra(t_env *env);
void					solve(t_env *env);
void					bfs_helper(t_env *env, int *parent, size_t u, int v);
void					init_bfs(t_env *env, t_queue *q);
void					bfs_uv(size_t *u, int *v, t_queue *q);
int						add_room(t_env *env, char *str);
int						add_pipe(t_env *env, char *str);
void					find_dim(t_env *env, char *l);
void					malloc_matrix(t_env *env, char ***matrix, size_t x);
void					malloc_graph(t_env *env);
void					free_queue(t_queue *q, int len, int flag);
void					free_env(t_env *env);
void					die(t_env *env);
int						quit(t_env *env);
void					find_all_paths(t_env *env);
void					clear_paths(t_env *env);
int						create_path(t_env *env, int *d, int i);
void					paths_from_residual(t_env *env, int flow);
void					reset_paths(t_env *env);
void					karp_helper(t_env *env, int *parent, int *u, int *v);
void					karp_loop(t_env *env, int **parent, int *u, int *v);
void					parse_wrapper(t_env *env);
size_t					queue_pop(t_queue *queue);
size_t					queue_pop_front(t_queue *queue);
void					queue_push(t_queue *queue, int v);
void					queue_push_front(t_queue *q, int u);
size_t					queue_pop_min(t_queue *q, int *d);
int						in_queue(t_queue q, int u);
void					queue_rotate(t_queue *q);
void					show_paths(t_env *env);
void					print_list(t_env *env);
void					print_shortest(t_env *env, size_t len, size_t ant);
void					print_paths(t_env *env);
void					print_queue(t_queue q);
void					print_graphs(t_env *env);
void					show_karp(t_env *env);
void					print_sol(t_env *env);
void					print_ants(t_env *env, t_queue paths[]);
void					init_window(t_env *env);
void					init_visu(t_env *env);
void					init_env(t_env *env);
void					create_map(t_env *env, int i);
void					draw_name(t_env *env, int ants);
void					visu(t_env *env, int a);
void					reset_clr(t_env *env);
int						key_release(int key, t_env *env);
void					draw_pipes(t_env *env, int a);
void					drawrectcircle(t_env *env, int i);
int						show_ants(t_env *env);
void					move_ants(t_env *env);
void					print_sol_visu(t_env *env);
void					mlx_draw(t_env *env);
void					rotate(t_queue *a, size_t len);
void					push(t_queue *a, int n);
void					drawthickline(t_env *env, t_point start, t_point end,
						int clr);
void					murphy_helper_one(t_env *env, t_murphy *m, t_ang *ang,
						t_point *start);
void					murphy_helper_two(t_murphy *m, t_ang *ang);
int						murphy_helper_three(t_env *env, t_murphy *m, t_ang *ang,
						int clr);
void					m_par(t_env *env, t_murphy *m, t_point pt, t_point p);
void					m_ite(t_env *env, t_murphy *m, t_ang *ang, int clr);
void					init_murphy(t_murphy *m, t_ang *ang, t_point *start,
						t_point *end);
void					check_oct(t_murphy *m, t_ang *ang, t_point *start);
void					murphy_helper_six(t_murphy *m, t_ang *ang);
void					init_murphy_two(t_murphy *m, t_ang *ang);
int						bren_init(t_bren *b, t_point start, t_point end);
int						bren_ite(t_bren *b);
int						bren_init(t_bren *b, t_point start, t_point end);
int						bren_ite(t_bren *b);
void					rotate_ants(t_env *env, t_queue paths[]);
void					push_ants(t_env *env, t_queue paths[], int *ants,
						int step);
void					calc_nite(t_env *env);
void					calc_diff(t_env *env);
int						all_done(t_env *env, t_queue paths[]);
void					init_pos(t_env *env, t_fpoint ants[env->flowmax]
						[env->vert - 1], t_queue paths[]);
void					nite_helper(t_env *env, int *min);
void					init_sol(t_env *env, t_queue paths[]);

#endif
