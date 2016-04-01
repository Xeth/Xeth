var ProfileView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("updateURI", "updateDetails", "updateName", "updateAvatar", "goToPreview");
        this.router = options.router;
        var data = {profile:this.model.toJSON()};
        this.$el = $(options.template(data));
        this.listenTo(this.model, "change:uri", this.updateURI);
        this.listenTo(this.model, "change:details", this.updateDetails);
        this.listenTo(this.model, "change:name", this.updateName);
        this.listenTo(this.model, "change:avatar", this.updateAvatar);
        
        this.$el.click(this.goToPreview);

    },

    updateURI:function(){
        this.$el.find(".uri .context").html(this.model.get("context"));
        this.$el.find(".uri .id").html(this.model.get("id"));
    },

    updateDetails:function(){
        this.updateName();
        this.updateAvatar();
    },

    updateName:function(){
        this.$el.find(".name").html(this.model.get("name"));
    },

    updateAvatar:function(){
        this.$el.find(".avatar img").attr("src", this.model.get("avatar"));
    },

    goToPreview: function(){
        this.router.redirect("bitprofile",{subpage:"view", args:{uri:this.model.get("uri")}});
    }


});

function ProfileViewFactory(template, router){
    this.create = function(model){return new ProfileView({model:model, template:template, router:router})}
    return this;
}

var BitprofilePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "add", "setExistingProfile");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("bitprofile");
        this.$el.html(this.template());
        this.templates = options.templates;
        this.filesystem = options.filesystem;
        this.accounts = options.accounts;
        this.profiles = options.profiles;
        this.registrars = options.registrars;
        this.fee = options.fee;
        this.menuEl = this.$el.find(".subNav.menu");
        this.menu = new MenuView({el: this.menuEl});
        this.router = options.router;//new PageRouter(this);
        
        this.factory = new ProfileViewFactory(options.templates.get("profile_item"), options.router);
        this.collection = new CollectionView({
			collection: options.profiles, 
			factory:this.factory,
			scroll:{scrollPage: this.$el.find(".bitprofileList")/*, step: 71*/},
			el: this.$el.find(".bitprofileList .holder"), 
            empty:this.$el.find(".empty")
		});
        this.collection.render();
        
        this.menuAlias = {default: "create"};
        this.subpages = {};
        this.subpages.view = new BitprofileViewPageView
        ({
            el:this.$el.find("#page_bitprofile_view"), 
            router:this.router, 
            profiles:this.profiles,
            templates:this.templates
        });
        var form = new BitprofileFormView
        ({
            accounts: this.accounts, 
            registrars: this.registrars,
            router:this.router, 
            templates:this.templates
        });
        this.subpages.create = new BitprofileCreatePageView
        ({
            el:this.$el.find("#page_bitprofile_create"), 
            profiles:this.profiles,
            fee: this.fee,
            form: form
        });
        this.subpages.edit = new BitprofileEditPageView
        ({
            el:this.$el.find("#page_bitprofile_edit"), 
            profiles:this.profiles,
            fee: this.fee,
            form: form
        });
        this.subpages.import = new BitprofileImportPageView
        ({
            filesystem:this.filesystem,
            profiles:this.profiles,
            el:this.$el.find("#page_bitprofile_import"),
            router:this.router, 
            templates:this.templates
        });
        this.subpages.export = new BitprofileExportPageView
        ({
            filesystem:this.filesystem,
            profiles:this.profiles,
        });
        this.subpages["default"] = this.subpages.create;
        this.menu.on("change", this.open);
        
        this.listenTo(this.profiles, "create", this.setPendingCreation);
        this.collection.collection.on("add", this.add);
    },

    render:function(args){
        if(args&&args.subpage){
            console.log(args);
            this.open(args.subpage,args.args);
        }
        else{
            this.open();
        }
    },
    
    open: function(name, args){
        if(!name || name instanceof Object){
            args = name;
            name = "default";
        }
        var view =  this.subpages[name];
        if(this.collection.collection.length>0 && (!args || args == name)) args = {uri:this.collection.collection.at(0).get("uri")};
        //if(this.menuAlias[name]=="edit" || name=="edit") args.page = "edit";
        if(this.menuAlias[name]=="export" || name=="export"){
            view.submit(args);
            return;
        }
        if(view!=undefined){
            if(this.active && this.active!=view) this.active.hide();
            this.active = view;
            this.menu.setCursor(this.menuAlias[name]||name);
            view.show(args);
        }
    },
    
    add:function(){
        notifySuccess("bitprofile created");
        this.setExistingProfile();
        this.open();
    },
    
    setExistingProfile: function(){
        this.menuEl.removeClass("new");
        this.menuEl.removeClass("pending");
        this.subpages["default"] = this.subpages.view;
        this.menuAlias = {default: "view"};
    },
    
    setPendingCreation: function(){
        this.menuEl.addClass("pending");
        this.menuEl.find(".import").hide();
    }

    
});
