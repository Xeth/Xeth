var BitprofileImportPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "render", "submit", "browse");
        SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("import_bitprofile");
        this.filesystem = options.filesystem;
        this.profiles = options.profiles;
        this.router = options.router;
    },
    
    render:function(){
        this.$el.html(this.template());
        this.$el.find(".btn.browse").click(this.browse);
        this.$el.find(".btnSubmit").click(this.submit);
        this.fileInput = this.$el.find("#importBitprofile_address");
    },

    open:function(){
        setTimeout(this.browse, 500);
    },

    browse:function(){
        var filename = this.filesystem.browse({type:"open"});
        if(filename) this.fileInput.val(filename);
    },

    submit:function(){
        var filename = this.fileInput.val();
        if(!filename){
            notifyError("please select a file");
            return false;
        }
        if(!this.profiles.importKey(filename)){
            notifyError("failed to import key, file is corrupted");
            return false;
        }
        notifySuccess("bitprofile imported");
        return true;
    }

});
