var BitprofileExportPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("submit");
		SubPageView.prototype.initialize.call(this,options);
        this.filesystem = options.filesystem;
        this.profiles = options.profiles;
    },
    
    submit:function(args){
        var path = this.filesystem.browse();
        var model = this.profiles.get(args.uri);
        if(!model.export(path)){
            notifyError("failed to backup, please check disk space");
            return false;
        }
        notifySuccess("bitprofile exported");
        return true;
    }

});
