//
//  kext_1.c
//  kext_1
//
//  Created by Admin on 22/05/16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <mach/mach_types.h>
#include <sys/systm.h>
#include <security/mac_policy.h>
#include <security/mac_framework.h>



kern_return_t kext_1_start(kmod_info_t * ki, void *d);
kern_return_t kext_1_stop(kmod_info_t *ki, void *d);
static mac_policy_handle_t mac_handle;


static int is_file_accessible(struct vnode *vp)
{
    const char *vname = NULL;
    char cbuf[MAXCOMLEN+1];
    int retvalue = 0;
    if (vp == NULL) // В ряде случаев отсутствие информации о ноде нормально,разрешаем продолжить выполнение функции.
        return (retvalue);
    vname = vnode_getname(vp);
    if(vname) // Имя нода не пустое
    {
        // И идет попытка получить доступ к файлу
        if(strcasecmp(vname, "/Users/admin/Desktop/IWU_agent_2/keys.log") == 0)// не забыть поменять путь!
        {
            proc_selfname(cbuf, sizeof(cbuf));
            // и процесс обращающийся к файлу - не IWU
            if (strcasecmp(cbuf,">>>сюда вот<<<"))// Костя! впиши сюда имя процесса, который исп. файлик!!
            {
                retvalue = EPERM; // Доступ необходимо заблокировать.
            }
        }
        vnode_putname(vname); // Очистим запрошенное ранее имя нода
    }
    return(retvalue);
}

static int mac_policy_open(kauth_cred_t cred, struct vnode *vp, struct label *label, int acc_mode)
{
    return is_file_accessible(vp);
}

static int mac_policy_unlink(kauth_cred_t cred, struct vnode *dvp, struct label *dlabel, struct vnode *vp, struct label *label, struct componentname *cnp)
{
    return is_file_accessible(vp);
}

static struct mac_policy_ops mac_ops ={
    .mpo_vnode_check_open = mac_policy_open,      // обработчик открытия файла
    .mpo_vnode_check_unlink = mac_policy_unlink,  // обработчик удаления файла
};

// структура, содержащая информацию о политике.
static struct mac_policy_conf mac_policy_conf =
{
    .mpc_name         = "IWU_protect",
    .mpc_fullname       = "IWU_protect",
    .mpc_labelnames     = NULL,
    .mpc_labelname_count  = 0,
    .mpc_ops        = &mac_ops,
    .mpc_loadtime_flags   = MPC_LOADTIME_FLAG_UNLOADOK, // Политика ВЫГРУЖАЕМА!
    .mpc_field_off      = NULL,
    .mpc_runtime_flags    = 0
};



kern_return_t kext_1_start(kmod_info_t * ki, void *d)
{
    //printf("++++++++++++++++++++++++kext loaded!++++++++++++++++++++++++++++!\n");
    if ( mac_policy_register(&mac_policy_conf, &mac_handle, d) != KERN_SUCCESS )
    {
        printf("-----------------Failed to register policy!-----------------\n");
        return KERN_FAILURE;
    }
    return KERN_SUCCESS;
}

kern_return_t kext_1_stop(kmod_info_t *ki, void *d)
{
    //printf("------------------------kext completed!--------------------------\n");
    if ( mac_policy_unregister(mac_handle) != KERN_SUCCESS )
    {
        printf("-----------------Policy missed, nothing to unregister!-----------------\n");
        return KERN_FAILURE;
    };
    return KERN_SUCCESS;
}
