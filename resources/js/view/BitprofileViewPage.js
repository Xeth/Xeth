var BitprofileViewPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("render");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("view_bitprofile");
        this.$el.html(this.template());
        this.profiles = options.profiles;
        this.router = options.router;
    },

    render:function(args){
        console.log(args.uri);
        if(this.model){
            this.stopListening(this.model);
        }
        this.model = this.profiles.get(args.uri);
        this.update();
        this.listenTo(this.model, "change:uri", this.updateURI);
        this.listenTo(this.model, "change:avatar",this.updateAvatar);
        this.listenTo(this.model, "change:name", this.updateName);
        this.listenTo(this.model, "change:payments", this.updateStealth);
    },
    
    update:function(model){
        this.updateURI();
        this.updateAvatar();
        this.updateName();
        this.updateStealth();
    },
    
    updateURI:function(){
        this.$el.find(".contextSelect input").val(this.model.get("context")+"@");
        this.$el.find(".bitprofileID input").val(this.model.get("id"));
    },
    
    updateAvatar:function(){
        var img = this.model.get("avatar");
        this.$el.find("input.avatarURL").val(img);
        this.$el.find(".avatar img").attr("src",((img)?img:'img/avatarEmpty.png'));
    },
    
    updateName:function(){
        this.$el.find("input.name").val(this.model.get("name"));
    },
    
    updateStealth:function(){
        var stealth = this.model.get("payments");
        this.$el.find(".stealthAddress .address").html(((stealth)?shortify(stealth, 21):'Stealth Account not linked'));
    }

});
