var Contact = Backbone.Model.extend({

    idAttribute: "alias",

    save:function(){
        if(this.isNew()){

            return addressbook.addContact(this.toJSON());
        }else{

            return addressbook.editContact(this.toJSON());
        }
    },

    destroy:function(){
        return addressbook.removeContact(this.get("alias"));
    },

    sync:function(){}

});

var AddressBook = Backbone.Collection.extend({

    model: Contact,

    fetch:function(){
        var contacts = addressbook.listContacts();
        if(contacts.length){
            this.reset(contacts);
        }else{
            if(this.length){
                this.reset();
            }
        }
    },

    rename:function(oldName, newName){

        if(addressbook.renameContact({oldName:oldName, newName:newName})){
            var contact = this.get(oldName);
            this.remove(contact, {silent:true});
            contact.set("alias", newName);
            this.add(contact, {silent: true});
            this.emit("update", contact);
            return true;
        }
        return false;
    },

    observe:function(){
        event.Contact.connect(this, Backbone.Collection.prototype.add);
    },


});
