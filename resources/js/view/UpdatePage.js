var UpdatePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "render", "submit", "browse", "updateClient");
        SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("update");
        this.filesystem = options.filesystem;
        this.config = options.config;
        this.info = options.info;
        this.router = options.router;
    },

    render:function(){
        this.$el.html(this.template());
        this.$el.find(".browse a").click(this.browse);
        this.$el.find(".btnSubmit").click(this.submit);
        this.fileInput = this.$el.find("#update_clientName");
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

        this.$el.find(".formpage").addClass("waiting");
        setTimeout(this.updateClient, 0, filename);
    },

    updateClient: function(filename){
        this.$el.find(".formpage").removeClass("waiting");
        if(this.config.updateEthereumClient(filename)){
            notifySuccess("client updated");
            this.info.update();
            this.router.redirect("settings");
        }
        return true;
    }

});
