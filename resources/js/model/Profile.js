
var Profile = Backbone.Model.extend({

    idAttribute: "uri",

    get:function(key){
        if(key=="uri"||key=="id"||key=="context"||key=="account")
        {
            return Backbone.Model.prototype.get.call(this, key);
        }
        return XETH_bitprofile.getData({uri:this.getURI(), key:key})||"";
    },

    getURI:function(){
        return Backbone.Model.prototype.get.call(this, "uri");
    },

    exportKey:function(path){
        var request = {path: path, uri:this.getURI()}
        return XETH_bitprofile.exportProfile(request);
    },

    linkStealthAddress:function(request){
        request.uri = this.getURI();
        return XETH_bitprofile.linkStealthAddress(request);
    },

    changeURI:function(request){
        request.uri = this.getURI();
        return XETH_bitprofile.moveProfile(request);
    },

    changeDetails:function(request){
        request.uri = this.getURI();
        return XETH_bitprofile.updateDetails(request);
    }

});

var ProfileCollection = Backbone.Collection.extend({

    initialize:function(models, options){
        _(this).bindAll("triggerError");
        options.events.onError("bitprofile", this.triggerError);
        options.events.onData("bitprofile", this.triggerData);
    },

    fetch:function(){
        var profiles = XETH_bitprofile.listProfiles();
        if(profiles.length){
            this.reset(profiles);
        }else{
            if(this.length){
                this.reset();
            }
        }
    },

    create:function(data){
        return XETH_bitprofile.createProfile(data);
    },
    
    importKey:function(path){
        return XETH_bitprofile.importProfile(path);
    },

    findProfile:function(uri, callback){
        var profile = this.find({uri:uri});
        if(profile) callback(profile);
    },

    exportKey:function(uri, path){
        this.findProfile(uri,function(profile){
            profile.exportKey(path);
        });
    },

    observe:function(){
        XETH_event.Profile.connect(this, this.add);
        XETH_event.ProfileRename.connect(this, this.triggerRename);
    },

    triggerRename:function(event){
        this.findProfile(event.oldURI, function(profile){
            profile.set(event);
        });
    },

    triggerData:function(event){
        this.findProfile(event.uri, function(profile){
            profile.set(event.key, event.value);
        });
    },

    triggerError:function(event){
        this.trigger("error", event.message);
        this.findProfile(event.uri, function(profile){
            profile.trigger("error", event.message);
        });
    },

    model: Profile
});
