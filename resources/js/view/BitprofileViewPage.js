var BitprofileViewPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "updateURI", "updateDetails", "updateStealth");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("view_bitprofile");
        this.$el.html(this.template());
        this.profiles = options.profiles;
        this.router = options.router;
    },
    
    render:function(){
        this.$el.html(this.template());
    },
    
    exit:function(){
        if(this.model){
            this.stopListening(this.model);
        }
    },

    open:function(args){
        console.log(args.uri);
        this.exit();
        this.model = this.profiles.find({uri:args.uri});
        this.update();
        this.listenTo(this.model, "change:uri", this.updateURI);
        this.listenTo(this.model, "change:details",this.updateDetails);
        this.listenTo(this.model, "change:payments", this.updateStealth);
    },
    
    update:function(model){
        this.updateURI();
        this.updateDetails();
        this.updateStealth();
    },
    
    updateURI:function(){
        this.$el.find(".contextSelect input").val(this.model.get("context")+"@");
        this.$el.find(".bitprofileID input").val(this.model.get("id"));
    },
    
    updateDetails:function(details){
        if(!details) details = this.model.get("details");
        this.$el.find(".avatar img").attr("src",((details.avatar)?details.avatar:'img/avatarEmpty.png'));
        this.$el.find("input.name").val(details.name||"");
    },
    
    
    updateStealth:function(){
        var stealth = this.model.get("payments");
        this.$el.find(".stealthAddress .address").html(((stealth)?shortify(stealth, 21):'Stealth Account not linked'));
    }

});
