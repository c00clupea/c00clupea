/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_passwd.c
 * created: 	Mon Feb  9 06:37:02 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "coreutils/c00s_passwd.h"

static char *new_password(const struct passwd *pw, uid_t myuid)
{
	char *orig = (char*)"";
	char *newp = NULL;
	char *cp = NULL;
	char *ret = NULL;

	if(myuid != 0 && pw->pw_passwd[0]) {
		orig = c00_ask_stdin("Old password: ");
		if(!orig) {
			goto error;
		}
		if(strcmp(orig,pw->pw_passwd) != 0) {
			C00STDOUTN("Incorrect password\n");
			goto error;
		}
	}
	orig = xstrdup(orig);
	newp = c00_ask_stdin("New password: ");
	if(!newp){
		goto error;
	}
	newp = xstrdup(newp);

	cp = c00_ask_stdin("Retype password: ");
	if(!cp){
		goto error;
	}
	if(strcmp(cp,newp) != 0){
		C00STDOUTN("Passwords don't match\n");
		goto error;
	}
	ret = newp;
error:
	free(orig);
	free(newp);
	return ret;

}

int PASSWD_MAIN(int argc, char *argv[])
{
	enum {
		OPT_algo   = (1 << 0), /* -a - password algorithm */
		OPT_lock   = (1 << 1), /* -l - lock account */
		OPT_unlock = (1 << 2), /* -u - unlock account */
		OPT_delete = (1 << 3), /* -d - delete password */
		OPT_lud    = OPT_lock | OPT_unlock | OPT_delete,
	};

	unsigned opt;
	const char *filename;
	char *myname;
	char *name;
	char *newp;
	char c;

	

	struct passwd *pw;
	struct passwd *otherpw;

	const char *opt_a = "";

	opt = getopt32(argv, "a:lud", &opt_a);

	argv += optind;

	pw = malloc(sizeof(struct passwd));
	otherpw = malloc(sizeof(struct passwd));
	check(c00h_actualuser(pw),"check returned %d",ERROR);

	if ((opt & OPT_lud) && (pw->pw_uid != 0 || !argv[0])){
		fprintf(stdout,"%s[OPTIONS] [USER]","");
		exit(0);
	}

	name = argv[0] ? argv[0] : pw->pw_name;
	
	if (strcmp(name,pw->pw_name) != 0){
		if(c00h_userbyname(otherpw,name) != TRUE)
		{
			C00STDOUTEXIT("User %s not found\n",1,name);
		}
		
	} else {
		otherpw = pw;
	}


//	C00DEBUG("Act User %s %s %d %d %s %s",pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
	
	if (pw->pw_uid != 0 && otherpw->pw_name != pw->pw_name){
		C00STDOUTEXIT("%s can't change password for %s\n",1,pw->pw_name,name);
	}
	newp = NULL;
	c = otherpw->pw_passwd[0] - '!';
	if(!(opt & OPT_lud)) {
		if (pw->pw_uid != 0 && !c) {
			C00STDOUTEXIT("can't change locked password for %s\n",1,otherpw->pw_name);
		}
		C00STDOUT("Changing password for %s\n",otherpw->pw_name);
		newp = new_password(otherpw,pw->pw_uid);
		if(!newp){
			C00STDOUTEXIT("password for %s is unchanged\n",1,otherpw->pw_name);
		}
	}

	free(pw);
	free(otherpw);
	
	return TRUE;

error:
	return ERROR;
}
